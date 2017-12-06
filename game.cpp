#include "precomp.h" // include (only) this in every .cpp file
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "Material.h"
#include "PointLight.h"
#include "Camera.h"


vector<Sphere> spheres;
vector<Plane> planes;
vector<PointLight> lights;
Camera *camera;
// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
	//Spheres
	spheres.push_back(Sphere(vec3(4.0f, 3.0f, -30.0f), 1, vec3(0.0, 1.0, 0.0), 0, 0));
	spheres.push_back(Sphere(vec3(-5.0f, 3.0f, -20.0f), 1, vec3(1.0, 1.0, 1.0), 2, 0));
	spheres.push_back(Sphere(vec3(4.0f, -2.0f, -20.0f), 1, vec3(1.0, 1.0, 1.0), 1, 0));
	

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

//Find intersection with object and return color
vec3 Game::trace(Ray r, vector<Sphere> &spheres, vector<Plane> &planes, int &depth)
{
	//Nearest obj hit
	float tnearSphere = std::numeric_limits<float>::infinity();
	float tnearPlane = std::numeric_limits<float>::infinity();
	Sphere *sphere = NULL;
	sphere->Sphere::traceRay(r, spheres, sphere, tnearSphere);
	Plane *plane = NULL;
	plane->Plane::traceRay(r, planes, plane, tnearPlane);
	//The final pixel color
	vec3 pixCol = 0;
	float bias = 1e-4;

	//If ray miss, return bg color
	if (sphere == NULL && plane == NULL)
		return vec3(0.5f, 0.5f, 0.5f);

	//If a sphere is closer
	if (tnearSphere < tnearPlane)
	{
		//Point of collision and normal
		vec3 posHit = r.orig + r.dir * tnearSphere;
		vec3 normHit = posHit - sphere->pos;

		//Normalize the normal vector
		normHit.normalize();

		bool inside = false;

		if (r.dir.dot(normHit) > 0)
		{
			normHit = -normHit;
			inside = true;
		}

		//If the material is reflective or transparent continue tracing
		if (sphere->mat->reflect && depth < 3)
		{
			//Compute the new reflected direction in which we check
			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
			reflDir.normalize();
			Ray *tempRay = new Ray(reflDir, posHit + normHit * bias);
			depth++;

			vec3 reflect = trace(*tempRay, spheres, planes, depth);

			pixCol += reflect;
		}
		else if (sphere->mat->transp && depth < 3)
		{
			//Material density and resulting angle
			float ior = 1.3;
			float dens = (inside) ? ior : 1 / ior;
			float cosAng = -normHit.dot(r.dir);
			float snell = 1 - dens*dens * (1 - cosAng*cosAng);

			//Compute the new refracted direction in which we check
			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
			refrDir.normalize();
			Ray *tempRay = new Ray(refrDir, posHit - normHit * bias);
			depth++;

			vec3 refract = trace(*tempRay, spheres, planes, depth);

			pixCol += refract;
		}
		else
			pixCol += sphere->getLighting(lights, spheres, posHit, normHit, bias);
		//If material is diffuse return its color and stop tracing
		pixCol *= sphere->color;
	}

	//If a plane is closer
	else if(tnearPlane < tnearSphere)
	{
		//Point of collision and normal
		vec3 posHit = r.orig + r.dir * tnearPlane;
		vec3 normHit = posHit - plane->pos;

		//Normalize the normal vector
		normHit.normalize();

		//If the material is reflective or transparent continue tracing
		if (plane->mat->reflect && depth < 3)
		{
			//Compute the new reflected direction in which we check
			vec3 reflDir = r.dir - normHit * 2 * r.dir.dot(normHit);
			reflDir.normalize();
			Ray *tempRay = new Ray(reflDir, posHit + normHit * bias);
			depth++;

			vec3 reflect = trace(*tempRay, spheres, planes, depth);

			pixCol += reflect;
		}
		else if (plane->mat->transp && depth < 3)
		{
			//Material density and resulting angle
			float ior = 1.3;
			float dens = 1.0f / ior;
			float cosAng = -normHit.dot(r.dir);
			float snell = 1 - dens*dens * (1 - cosAng*cosAng);

			//Compute the new refracted direction in which we check
			vec3 refrDir = r.dir*dens + normHit*(dens*cosAng - sqrt(snell));
			refrDir.normalize();
			Ray *tempRay = new Ray(refrDir, posHit - normHit * bias);
			depth++;

			vec3 refract = trace(*tempRay, spheres, planes, depth);

			pixCol += refract;
		}
		else
			pixCol += plane->getLighting(lights, planes, posHit, normHit, bias);
		//If material is diffuse return its color and stop tracing
		pixCol *= plane->color;
	}

	return pixCol;
}

void Game::render(vector<Sphere> &spheres, vector<Plane> &planes, Camera *cam)
{
	unsigned width = screen->GetWidth(), height = screen->GetHeight();
	vec3 pixel;
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

			pixel = trace(*r, spheres, planes, depth);
		
			int red = (int)((pixel.x) * 255.0);
			int green = (int)((pixel.y) * 255.0);
			int blue = (int)((pixel.z) * 255.0);

			Pixel c = blue + (green << 8) + (red << 16);
			screen->Plot(x, y, c);
		}
}

void KeyDown(int key)
{
	switch (key)
	{
		case 'w' :
			camera->fov++;
			break;
		case 's':
			camera->fov--;
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

	render(spheres, planes, camera);

}