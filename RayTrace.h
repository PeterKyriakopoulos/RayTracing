#pragma once
#include "Ray.h"
#include "Plane.h"
#include "Sphere.h"
#include <vector>

class RayTrace
{
public:
	RayTrace();
	~RayTrace();

	vec3 trace(Ray r, vector<Sphere> &sphere, vector<Plane> &planes, vector<PointLight> &lights, int &depth);
	void render(vector<Sphere> &sphere, vector<Plane> &planes, vector<PointLight> &lights, Camera *cam, Surface *screen);
};

