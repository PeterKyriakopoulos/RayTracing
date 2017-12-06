#include "precomp.h"
#include "Plane.h"
#include "Ray.h"
#include "Material.h"


Plane::Plane(const vec3 &position, const vec3 &normal, const vec3 &color, const int type) : Object(position, type, color), norm(normalize(normal))
{
}

//Check if ray intersects plane
const Intersection Plane::intersect(const Ray & r) const
{
	Intersection intersect(&r, this, -1.0f);

	float den = norm.dot(r.dir);
	if (den > 1e-6)
	{
		vec3 l = position - r.orig;
		float t = l.dot(norm) / den;

		intersect.rayT = -t / den;
	}

	return intersect;
}

const SurfaceData Plane::getSurfaceData(const Intersection & intersection) const
{
	const vec3 &surfacePoint = intersection.getIntersectionPosition();

	return{norm, surfacePoint};
}


