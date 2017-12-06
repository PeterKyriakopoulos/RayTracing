#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include "Plane.h"
#include "Material.h"
#include "PointLight.h"
#include "Camera.h"
#include "RayTrace.h"
#include <sstream>
#include <conio.h>

vector<Sphere> spheres;
vector<Plane> planes;
vector<PointLight> lights;
Camera *camera;
RayTrace rendering;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Spheres
	spheres.push_back(Sphere(vec3(4.0f, 3.0f, -20.0f), 1, vec3(0.0, 1.0, 0.0), 0, 0));
	spheres.push_back(Sphere(vec3(-5.0f, 3.0f, -20.0f), 1, vec3(1.0, 1.0, 1.0), 2, 0));
	spheres.push_back(Sphere(vec3(4.0f, -2.0f, -20.0f), 1, vec3(1.0, 1.0, 1.0), 1, 0));
	spheres.push_back(Sphere(vec3(-3.0f, -2.0f, -25.0f), 3, vec3(1.0, 1.0, 1.0), 1, 0));
	spheres.push_back(Sphere(vec3(4.0f, 3.0f, -15.0f), 1, vec3(1.0, 1.0, 1.0), 2, 0));
	

	//Planes
	planes.push_back(Plane(vec3(0.0f, -10.0f, -30.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0, 0.8, 0.0), 0));
	planes.push_back(Plane(vec3(-6.0f, 0.0f, -40.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.5, 0.0, 1.0), 0));
	planes.push_back(Plane(vec3(0.0f, -6.0f, -40.0f), vec3(0.0f, -1.0f, 0.0f), vec3(1.0, 1.0, 1.0), 0));
	planes.push_back(Plane(vec3(6.0f, 0.0f, -40.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.5, 0.0, 1.0), 0));
	planes.push_back(Plane(vec3(0.0f, 6.0f, -40.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0, 1.0, 1.0), 0));
	planes.push_back(Plane(vec3(0.0f, -8.0f, -15.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 0.8, 0.0), 0));


	//Lights
	lights.push_back(PointLight(vec3(0.0f, 10.0f, -10.0f), 650.0f, vec3(1.0f, 1.0f, 1.0f)));

	camera = new Camera(vec3(0, 0, 0), vec3(45), 30);
}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

void Game::KeyDown(int key)
{
	switch (key)
	{
		case 'w':
			//glTranslatef();
			break;
	}
}

// -----------------------------------------------------------
// Main application tick function
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
	// clear the graphics window
	screen->Clear(0);

	rendering.render(spheres, planes, lights, camera, screen);

	//char key = getch();
	//int asciiVal = key;

	//KeyDown(asciiVal);
}