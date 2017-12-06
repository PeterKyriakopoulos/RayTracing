#pragma once
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"

class RayTrace
{
public:
	RayTrace();
	~RayTrace();

	const vec3 castRay(const Ray &r, const int depth, vector<Object*> objects, vector<Light*> lights) const;
	const Intersection findNearestObjectIntersection(const Ray &r, vector<Object*> objects, Object* &object) const;
	const vec3 lighting(const Ray &castRay, vector<Object*> objects, vector<Light*> lights, Object* object, const SurfaceData &surfaceData, const int depth) const;
};

