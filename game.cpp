#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"
#include "Camera.h"
#include <vector>


vector<Sphere> spheres;
Camera *camera;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	spheres.push_back(Sphere(vec3(1, -0.2, 0), 1, vec3(0.0, 1.0, 0.0), 0));
	spheres.push_back(Sphere(vec3(200, 200, 0), 5, vec3(1.0, 1.0, 1.0), 1));

	camera = new Camera(vec3(2, 2, 2), vec3(45), 30);
}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

//Find intersection with object and return color
vec3 Game::trace(Ray r, vector<Sphere> &spheres, int &depth)
{
	//Nearest obj hit
	float tnear = std::numeric_limits<float>::infinity();
	//Sphere *sphere = NULL;
	bool hit = FALSE;

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
				//sphere = spheres[i];
				hit = TRUE;
			}
		}

		//If ray miss, return black color
		if (!hit)
			return vec3(0);

		//The final pixel color
		vec3 pixCol = 0;
		//Point of collision and normal
		vec3 posHit = r.orig + r.dir * tnear;
		vec3 normHit = posHit - spheres[i].pos;

		//Normalize the normal vector
		normHit.normalize();

		//If the material is reflective or transparent continue tracing
		if (spheres[i].mat->reflect && depth < 3)
		{
			//Compute the new reflected direction in which we check
			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
			Ray *tempRay = new Ray(reflDir, posHit + normHit);
			depth++;

			vec3 reflect = trace(*tempRay, spheres, depth);

			return reflect * pixCol;
		}
		else if (spheres[i].mat->transp && depth < 3)
		{
			//Material density and resulting angle
			float dens = 1 / 1.3;
			float cosAng = -normHit.dot(r.dir);
			float snell = dens*dens * (1 - cosAng*cosAng);

			//Compute the new refracted direction in which we check
			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
			refrDir.normalize();
			Ray *tempRay = new Ray(refrDir, posHit - normHit);
			depth++;

			vec3 refract = trace(*tempRay, spheres, depth);

			return refract * pixCol;
		}

		//If material is diffuse return its color and stop tracing
		return pixCol + spheres[i].color;
	}
}

void Game::render(vector<Sphere> &spheres, Camera *cam)
{
	unsigned width = screen->GetWidth()/cam->pos.x, height = screen->GetHeight()/cam->pos.y;
	vec3 pixel;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = cam->fov;
	float aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5 * fov / 180);

	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < width; x++)
		{
			int depth = 0;
			float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
			Ray *r = new Ray(vec3(xx, yy, -1), vec3(0));
			r->dir.normalize();

			pixel = trace(*r, spheres, depth);
		
			int red = (int)((pixel.x) * 255.0);
			int green = (int)((pixel.y) * 255.0);
			int blue = (int)((pixel.z) * 255.0);

			Pixel c = blue + (green << 8) + (red << 16);
			screen->Plot(x, y, c);
		}
}

static Sprite rotatingGun( new Surface( "assets/aagun.tga" ), 36 );
static int frame = 0;

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	/* How to plot the color of a pixel
	screen.Plot(x,y,c)
	r = (int) ((cc.x) * 255.0))
	c = b+ (g<<8) + (r<<16)
	*/

	// clear the graphics window
	screen->Clear(0);
	// print something in the graphics window
	//screen->Print( "pete is the man", 2, 2, 0xffffff );
	// print something to the text window
	//printf( "this goes to the console window.\n" );
	// draw a sprite
	//rotatingGun.SetFrame( frame );
	//rotatingGun.Draw( screen, 100, 100 );

	render(spheres, camera);


	if (++frame == 36) frame = 0;
}