#pragma once
#include "template.h"
#include "Ray.h"
#include "Material.h"
#include "Object.h"
#include "Intersection.h"
#include "SurfaceData.h"
#include <vector>


class Sphere : public Object
{
public:
	Sphere(const vec3 &position, const float radius, const vec3 &color, const int type);
	const Intersection intersect(const Ray &r) const;
	const SurfaceData getSurfaceData(const Intersection &intersection) const;

	float rad;
};

