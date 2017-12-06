#pragma once
#include "Ray.h"
#include "Material.h"
#include "SurfaceData.h"

class Intersection;

class Object {

public:
	const Material *mat;
	vec3 position;
	vec3 color;

	Object(const vec3 &position, const int type, const vec3 &color);
	Object(const Material *material);

	virtual const Intersection intersect(const Ray &ray) const = 0;
	virtual const SurfaceData getSurfaceData(const Intersection &intersection) const = 0;

	inline const Material& getMaterial() const { return *mat; }
};

