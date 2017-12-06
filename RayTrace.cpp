#include "precomp.h"
#include "RayTrace.h"


RayTrace::RayTrace()
{
}


RayTrace::~RayTrace()
{
}

//Return color of object intersected or background
const vec3 RayTrace::castRay(const Ray & r, const int depth, vector<Object*> objects, vector<Light*> lights) const
{
	//Go to a max recursive depth
	if (depth > 3)
		return vec3(0.0f, 0.0f, 0.0f);

	Object* object = NULL;

	//Return nearest obj intersected
	const Intersection &intersection = findNearestObjectIntersection(r, objects, object);

	//Check if intersection exists
	if (intersection.isIntersecting()) 
	{
		const SurfaceData &surfaceData = intersection.object->getSurfaceData(intersection);

		return lighting(r, objects, lights, object, surfaceData, depth);
	}
	else
		return vec3(0.5f, 0.5f, 0.5f);
}

//Return the nearest position and object intersected
const Intersection RayTrace::findNearestObjectIntersection(const Ray & r, vector<Object*> objects, Object* &object) const
{
	Intersection tnear;

	for (auto i = objects.begin(); i != objects.end(); i++) 
	{
		const Intersection &intersect = (*i)->intersect(r);

		if (intersect.isIntersecting() && (!tnear.isIntersecting() || intersect.rayT < tnear.rayT))
		{
			tnear = intersect;
			object = *i;
		}
	}

	return tnear;
}

const vec3 RayTrace::lighting(const Ray & castRay, vector<Object*> objects, vector<Light*> lights, Object* object, const SurfaceData & surfaceData, const int depth) const
{
	//Final pixel color
	vec3 pixCol = 0;
	float bias = 1e-4;
	vec3 norm = surfaceData.norm;
	norm.normalize();
	vec3 reflectBias = bias * norm;
	Object* newObj = NULL;

	if (object->mat->diffuse == true)
	{
		for (auto j = lights.begin(); j < lights.end(); j++)
		{
			vec3 lightDir = (*j)->getLightVector(surfaceData.pos);
			Ray *shadow = new Ray(lightDir, surfaceData.pos + (bias * surfaceData.norm));
			Intersection shadowInt = findNearestObjectIntersection(*shadow, objects, newObj);
				
			if (!shadowInt.isIntersecting() || shadowInt.rayT > (*j)->distanceToPoint(shadow->orig))
			{
				pixCol += (*j)->getColorAndIntensity(surfaceData.pos) * std::_Max_value(0.0f, norm.dot(lightDir)) * object->color;
			}
			else if (shadowInt.object->mat->reflect)
			{
				SurfaceData shadowObjectSurfacePoint = shadowInt.object->getSurfaceData(shadowInt);
				pixCol += (*j)->getColorAndIntensity(surfaceData.pos) *
					std::_Max_value(0.0f, norm.dot(lightDir)) *	0.9f;
			}
		}
	}
	else if (object->mat->reflect == true)
	{
		bool outside = false;
		if (dot(castRay.dir, norm) < 0)
			outside = true;

		vec3 reflDir = castRay.dir - norm * 2 * castRay.dir.dot(norm);
		reflDir.normalize();
		vec3 reflOrig = outside ? surfaceData.pos + reflectBias : surfaceData.pos - reflectBias;
		Ray *reflectionRay = new Ray(reflDir, reflOrig);

		vec3 reflect = RayTrace::castRay(*reflectionRay, depth + 1, objects, lights);

		pixCol += reflect;
	}
	else if (object->mat->transp == true)
	{
		bool outside = false;
		if (dot(castRay.dir, norm) < 0)
			outside = true;

		//Material density and resulting angle
		float ior = 1.1;
		float dens = (outside) ? 1/ior :  ior;
		float cosAng = -norm.dot(castRay.dir);
		float snell = 1 - dens*dens * (1 - cosAng*cosAng);

		vec3 refrDir = castRay.dir*dens + norm*(dens*cosAng - sqrt(snell));
		refrDir.normalize();
		vec3 refrOrig = outside ? surfaceData.pos - reflectBias : surfaceData.pos + reflectBias;
		Ray *refractionRay = new Ray(refrDir, refrOrig);

		vec3 refract = RayTrace::castRay(*refractionRay, depth + 1, objects, lights);

		pixCol += refract;
	}

	return pixCol;
}

