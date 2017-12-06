#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Material.h"
#include "Object.h"
#include "Light.h"
#include "PointLight.h"
#include "RayTrace.h"
#include "Camera.h"


vector<Sphere> spheres;
vector<Plane> planes;
vector<Object*> objects;
vector<Light*> lights;
Camera *camera;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Spheres
	//spheres.push_back(Sphere(vec3(4.0f, 3.0f, -30.0f), 1, vec3(0.0, 1.0, 0.0), 0, 0));
	//spheres.push_back(Sphere(vec3(-5.0f, 3.0f, -30.0f), 1, vec3(1.0, 1.0, 0.0), 1, 0));
	objects.push_back(new Sphere(vec3(4.0f, 3.0f, -30.0f), 1.0f, vec3(0.0f, 1.0f, 0.0f), 0));
	objects.push_back(new Sphere(vec3(-5.0f, 3.0f, -30.0f), 1.0f, vec3(1.0f, 1.0f, 0.0f), 0));

	//Planes
	//planes.push_back(Plane(vec3(-6.0f, 0.0f, -30.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.5, 1.0, 1.0), 0));
	objects.push_back(new Plane(vec3(0.0f, 0.0f, -30.0f), vec3(0.0f, 0.0f, 1.0f), vec3(1.0, 1.0, 1.0), 0));
	//objects.push_back(new Plane(vec3(10.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(1.0, 1.0, 1.0), 0));

	//Lights
	//spheres.push_back(Sphere(vec3(0.0f, 10.0f, -10.0f), 3, 0, 0, vec3(1.0, 1.0, 1.0)));
	lights.push_back(new PointLight(vec3(0.0f, 10.0f, -20.0f), 1000.0f, vec3(1.0f, 1.0f, 1.0f)));


	camera = new Camera(vec3(2, 2, 2), vec3(45), 30);
}

// -----------------------------------------------------------
// Close down application
// -----------------------------------------------------------
void Game::Shutdown()
{
}

//bool Game::trace(Ray r, vector<Object> &objects, float &tnear, Object *&hitObject)
//{
//	tnear = std::numeric_limits<float>::infinity();
//
//	for (int i=0 ; i!= objects.size(); i++)
//	{
//		float t = std::numeric_limits<float>::infinity();
//
//		if (objects[i].intersect(r, t) && t < tnear)
//		{
//			hitObject = &objects[i];
//			tnear = t;
//		}
//	}
//
//}
//
//vec3 Game::castRay(Ray r, vector<Object> &objects)
//{
//	vec3 pixCol = 0;
//	Object *hitObj = NULL;
//	float t;
//
//	if (trace(r, objects, t, hitObj))
//	{
//		vec3 posHit = r.orig + r.dir * t;
//		vec3 normHit;
//
//		hitObj->getData(posHit, normHit);
//
//		pixCol = std::_Max_value(0.f, normHit.dot(-r.dir));
//	}
//
//	return pixCol;
//}

////Find intersection with object and return color
//vec3 Game::trace(Ray r, vector<Sphere> &spheres, vector<Plane> &planes, int &depth)
//{
//	//Nearest obj hit
//	float tnearSphere = std::numeric_limits<float>::infinity();
//	float tnearPlane = std::numeric_limits<float>::infinity();
//	Sphere *sphere = NULL;
//	sphere->Sphere::traceRay(r, spheres, sphere, tnearSphere);
//	Plane *plane = NULL;
//	plane->Plane::traceRay(r, planes, plane, tnearPlane);
//	//The final pixel color
//	vec3 pixCol = 0;
//	float bias = 1e-4;
//
//	//If ray miss, return bg color
//	if (sphere == NULL && plane == NULL)
//		return vec3(0.5f, 0.5f, 0.5f);
//
//	//If a sphere is closer
//	if (tnearSphere < tnearPlane)
//	{
//		//Point of collision and normal
//		vec3 posHit = r.orig + r.dir * tnearSphere;
//		vec3 normHit = posHit - sphere->pos;
//
//		//Normalize the normal vector
//		normHit.normalize();
//
//		bool inside = false;
//
//		if (r.dir.dot(normHit) > 0)
//		{
//			normHit = -normHit;
//			inside = true;
//		}
//
//		//If the material is reflective or transparent continue tracing
//		if (sphere->mat->reflect && depth < 3)
//		{
//			//Compute the new reflected direction in which we check
//			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
//			reflDir.normalize();
//			Ray *tempRay = new Ray(reflDir, posHit + normHit * bias);
//			depth++;
//
//			vec3 reflect = trace(*tempRay, spheres, planes, depth);
//
//			pixCol += reflect;
//		}
//		else if (sphere->mat->transp && depth < 3)
//		{
//			//Material density and resulting angle
//			float ior = 1.1;
//			float dens = (inside) ? ior : 1 / ior;
//			float cosAng = -normHit.dot(r.dir);
//			float snell = 1 - dens*dens * (1 - cosAng*cosAng);
//
//			//Compute the new refracted direction in which we check
//			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
//			refrDir.normalize();
//			Ray *tempRay = new Ray(refrDir, posHit - normHit * bias);
//			depth++;
//
//			vec3 refract = trace(*tempRay, spheres, planes, depth);
//
//			pixCol += refract;
//		}
//		else
//			pixCol += sphere->getLighting(spheres, posHit, normHit, bias);
//		//If material is diffuse return its color and stop tracing
//		pixCol *= sphere->color;
//	}
//
//	//If a plane is closer
//	else if(tnearPlane < tnearSphere)
//	{
//		//Point of collision and normal
//		vec3 posHit = r.orig + r.dir * tnearPlane;
//		vec3 normHit = posHit - plane->pos;
//
//		//Normalize the normal vector
//		normHit.normalize();
//
//		//If the material is reflective or transparent continue tracing
//		if (plane->mat->reflect && depth < 3)
//		{
//			//Compute the new reflected direction in which we check
//			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
//			reflDir.normalize();
//			Ray *tempRay = new Ray(reflDir, posHit + normHit * bias);
//			depth++;
//
//			vec3 reflect = trace(*tempRay, spheres, planes, depth);
//
//			pixCol += reflect;
//		}
//		else if (plane->mat->transp && depth < 3)
//		{
//			//Material density and resulting angle
//			float ior = 1.1;
//			float dens = 1.0f / ior;
//			float cosAng = -normHit.dot(r.dir);
//			float snell = 1 - dens*dens * (1 - cosAng*cosAng);
//
//			//Compute the new refracted direction in which we check
//			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
//			refrDir.normalize();
//			Ray *tempRay = new Ray(refrDir, posHit - normHit * bias);
//			depth++;
//
//			vec3 refract = trace(*tempRay, spheres, planes, depth);
//
//			pixCol += refract;
//		}
//		else
//			pixCol += plane->getLighting(spheres, planes, posHit, normHit, bias);
//		//If material is diffuse return its color and stop tracing
//		pixCol *= sphere->color;
//	}
//
//	return pixCol;
//}

void Game::render(vector<Object*> objects, vector<Light*> lights, Camera *cam)
{
	unsigned width = screen->GetWidth(), height = screen->GetHeight();
	RayTrace pixel;
	vec3 plottedPixel;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	float fov = cam->fov;
	float aspectratio = width / float(height);
	float angle = tan(M_PI * 0.5f * fov / 180.0f);

	for (unsigned y = 0; y < height; y++)
		for (unsigned x = 0; x < width; x++)
		{
			int depth = 0;
			float xx = (2 * ((x + 0.5f) * invWidth) - 1) * angle * aspectratio;
			float yy = (1 - 2 * ((y + 0.5f) * invHeight)) * angle;
			Ray *r = new Ray(vec3(xx, yy, -1), vec3(0));
			r->dir.normalize();

			plottedPixel = pixel.castRay(*r, 0, objects, lights);
			//pixel = castRay(*r, objects);
		
			int red = (int)((plottedPixel.x) * 255.0);
			int green = (int)((plottedPixel.y) * 255.0);
			int blue = (int)((plottedPixel.z) * 255.0);

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

	render(objects, lights, camera);


	//if (++frame == 36) frame = 0;
}