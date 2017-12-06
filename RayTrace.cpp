#include "precomp.h"
#include "RayTrace.h"
#include "PointLight.h"


RayTrace::RayTrace()
{
}


RayTrace::~RayTrace()
{
}

//Find intersection with object and return color
vec3 RayTrace::trace(Ray r, vector<Sphere> &spheres, vector<Plane> &planes, vector<PointLight> &lights, int &depth)
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

			vec3 reflect = trace(*tempRay, spheres, planes, lights, depth);

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

			vec3 refract = trace(*tempRay, spheres, planes, lights, depth);

			pixCol += refract;
		}
		else
			pixCol += sphere->getLighting(lights, spheres, posHit, normHit, bias);
		//If material is diffuse return its color and stop tracing
		pixCol *= sphere->color;
	}

	//If a plane is closer
	else if (tnearPlane < tnearSphere)
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

			vec3 reflect = trace(*tempRay, spheres, planes, lights, depth);

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

			vec3 refract = trace(*tempRay, spheres, planes, lights, depth);

			pixCol += refract;
		}
		else
			pixCol += plane->getLighting(lights, planes, posHit, normHit, bias);
		//If material is diffuse return its color and stop tracing
		pixCol *= plane->color;
	}

	return pixCol;
}

void RayTrace::render(vector<Sphere> &spheres, vector<Plane> &planes, vector<PointLight> &lights, Camera *cam, Surface *screen)
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

			pixel = trace(*r, spheres, planes, lights, depth);

			int red = (int)((pixel.x) * 255.0);
			int green = (int)((pixel.y) * 255.0);
			int blue = (int)((pixel.z) * 255.0);

			Pixel c = blue + (green << 8) + (red << 16);
			screen->Plot(x, y, c);
		}
}
