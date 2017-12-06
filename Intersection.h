#pragma once
#include "Ray.h"
#include "Object.h"

class Intersection {
public:
	const Ray *r;
	const Object *object;
	float rayT;

	//For triangle intersections
	int triangleIndex;
	float u, v; 

	Intersection();
	Intersection(const Ray *r, const Object *object, const float rayT);

	inline bool isIntersecting() const { return rayT >= 0; }
	inline const vec3 getIntersectionPosition() const { return r->orig + r->dir * rayT; }
};

