#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
#include <vector>


Sphere *sphere1, *sphere2;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	vec3 p1, p2;
	p1 = (50, 50, 0);
	p2 = (75, 50, 0);
	sphere1 = new Sphere(p1, 10, (0.0, 255.0, 0.0), 0);
	sphere1 = new Sphere(p2, 10, (255.0, 255.0, 255.0), 1);


}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

//Find intersection with object and return color
vec3 Game::trace(Ray r, vector<Sphere> spheres, int &depth)
{
	//Nearest obj hit
	float tnear = std::numeric_limits<float>::infinity();
	Sphere *sphere = NULL;

	//Loop over all spheres
	for (uint i = 0; i < spheres.size(); i++)
	{
		float t0 = std::numeric_limits<float>::infinity();
		float t1 = std::numeric_limits<float>::infinity();

		//If ray hits, store the closest hit sphere
		if (spheres[i].intersect(r, t0, t1))
		{
			if (t0 < 0)
				t0 = t1;
			if (t0 < tnear)
			{
				tnear = t0;
				*sphere = spheres[i];
			}
		}

		//If ray miss, return black color
		if (!sphere)
			return vec3(0);

		//The final pixel color
		vec3 pixCol = 0;
		//Point of collision and normal
		vec3 posHit = r.orig + r.dir * tnear;
		vec3 normHit = posHit - sphere->pos;

		//Normalize the normal vector
		normHit = normalize(normHit);

		//If the material is reflective or transparent continue tracing
		if (sphere->mat->reflect && depth < 3)
		{
			//Compute the new reflected direction in which we check
			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
			Ray *tempRay = new Ray(reflDir, posHit + normHit);
			depth++;

			vec3 reflect = trace(*tempRay, spheres, depth);

			return reflect * pixCol;
		}
		else if (sphere->mat->transp && depth < 3)
		{
			//Material density and resulting angle
			float dens = 1 / 1.3;
			float cosAng = -normHit.dot(r.dir);
			float snell = dens*dens * (1 - cosAng*cosAng);

			//Compute the new refracted direction in which we check
			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
			refrDir = normalize(refrDir);
			Ray *tempRay = new Ray(refrDir, posHit - normHit);
			depth++;

			vec3 refract = trace(*tempRay, spheres, depth);

			return refract * pixCol;
		}

		//If material is diffuse return its color and stop tracing
		return pixCol + sphere->color;
	}
}

static Sprite rotatingGun( new Surface( "assets/aagun.tga" ), 36 );
static int frame = 0;

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::Tick( float deltaTime )
{
	/* How to plot the color of a pixel
	screen.Plot(x,y,c)
	r = (int) ((cc.x) * 255.0))
	c = b+ (g<<8) + (r<<16)
	*/


	// clear the graphics window
	screen->Clear( 0 );
	// print something in the graphics window
	screen->Print( "pete is the man", 2, 2, 0xffffff );
	// print something to the text window
	printf( "this goes to the console window.\n" );
	// draw a sprite
	rotatingGun.SetFrame( frame );
	rotatingGun.Draw( screen, 100, 100 );

	if (++frame == 36) frame = 0;
}