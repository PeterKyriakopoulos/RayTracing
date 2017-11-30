#pragma once
#include "template.h"
#include "Material.h"
#include "Ray.h"

class Plane
{
public:
	Plane(vec3 position, vec3 normal, vec3 color, int type);
	~Plane();
	bool intersect(Ray r, float &t);

	vec3 pos, color, norm;
	Material *mat;
};

