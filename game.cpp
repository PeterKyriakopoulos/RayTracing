#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include <vector>

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{

}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

//Find intersection with sphere and return color
vec3 Trace(Ray r, vector<Sphere> spheres, int depth)
{
	float tnear = std::numeric_limits<float>::infinity();
	Sphere *sphere = NULL;
	
	for (int i = 0; i < spheres.size(); i++)
	{
		float t0 = std::numeric_limits<float>::infinity();
		float t1 = std::numeric_limits<float>::infinity();

		//If ray hits, store the closest hit sphere
		if (spheres[i].intersect(r, &t0, &t1));
		{
			if (t0 < 0)
				t0 = t1;
			if (t0 < tnear)
			{
				tnear = t0;
				sphere = spheres[i];
			}
		}

		//If ray miss, return black color
		if (!sphere)
			return vec3(0);


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