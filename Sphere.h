#pragma once
#include "template.h"
#include "Ray.h"
#include "Material.h"


class Sphere
{
public:
	Sphere(vec3 position, float radius, vec3 color, int type);
	~Sphere();
	bool intersect(Ray r, float &t0, float &t1);

	vec3 pos, color;
	float rad;
	Material *mat;
};

