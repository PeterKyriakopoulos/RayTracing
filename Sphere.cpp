#include "precomp.h"
#include "Sphere.h"
#include "Ray.h"


Sphere::Sphere(const vec3 &position, const float radius, const vec3 &color, const int type) : Object(position, type, color), rad(radius)
{
}

bool solveQuadratic(float a,  float b, float c, float &t0, float &t1)
{
	//Solve quadratic 
	float discr = b * b - 4 * a * c;
	if (discr < 0)
		return false;
	else if (discr == 0)
		t0 = t1 = -0.5f * b / a;
	else
	{
		float q = (b > 0) ? -0.5f * (b + sqrt(discr)) : -0.5f * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}
	if (t0 > t1)
		swap(t0, t1);
	
	return true;
}

const Intersection Sphere::intersect(const Ray & r) const
{
	Intersection intersect(&r, this, -1.0f);

	vec3 L = r.orig - position;
	float a = dot(r.dir, r.dir);
	float b = 2 * dot(r.dir, L);
	float c = dot(L, L) - (rad * rad);
	float t0, t1;

	if (!solveQuadratic(a,b,c,t0,t1))
		return intersect;

	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return intersect;
	}

	intersect.rayT = t0;
	return intersect;
}

const SurfaceData Sphere::getSurfaceData(const Intersection & intersection) const
{
	const vec3 &surfacePoint = intersection.getIntersectionPosition();
	vec3 localCoord = surfacePoint - position;
	vec3 normal = normalize(localCoord);

	return{ normal, surfacePoint};
}









