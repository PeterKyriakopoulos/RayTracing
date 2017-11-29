#pragma once
#include "Sphere.h"
#include <vector>


class Ray
{
public:
	Ray(vec3 direction, vec3 origin);
	~Ray();	
	vec3 trace(vector<Sphere> spheres, int &depth);

	vec3 dir;
	vec3 orig;
};

