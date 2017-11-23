#include "precomp.h" // include (only) this in every .cpp file

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