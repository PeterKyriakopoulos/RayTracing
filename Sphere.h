#pragma once
#include "template.h"


class Sphere
{
public:
	Sphere(vec3 position, float radius);
	~Sphere();
	bool Intersect(Ray r);

	vec3 pos;
	float rad;
};

