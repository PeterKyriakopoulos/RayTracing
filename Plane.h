#pragma once
#include "template.h"
#include "Material.h"
#include "Ray.h"
#include "Object.h"
#include "Intersection.h"
#include "SurfaceData.h"
#include <vector>

class Plane : public Object 
{
public:
	Plane(const vec3 &position, const vec3 &normal, const vec3 &color, const int type);
	const Intersection intersect(const Ray &r) const;
	const SurfaceData getSurfaceData(const Intersection &intersection) const;

	vec3 norm;
};

