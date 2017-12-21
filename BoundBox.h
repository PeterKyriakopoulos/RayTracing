#pragma once
#include "precomp.h"
#include "Ray.h"

class BoundBox
{
public:
	BoundBox(const vec3 &min, const vec3 &max);
	BoundBox(const vec3 &p);
	bool intersect(const Ray &r, float *tnear, float *tfar) const;
	void expand(const vec3 &p);
	void expand(const BoundBox& b);
	uint maxDim() const;
	float surface() const;
	~BoundBox();


	vec3 minim, maxim, extent;
};

