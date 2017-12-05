#pragma once
#include "Ray.h"

class Object
{
public:
	Object();
	~Object();
	bool intersect(Ray &, float &);
	void getData(vec3 &, vec3 &);

	vec3 color;
};

