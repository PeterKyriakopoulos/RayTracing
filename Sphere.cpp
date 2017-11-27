#include "precomp.h"
#include "Sphere.h"
#include "Ray.h"
#include "Material.h"


Sphere::Sphere(vec3 position, float radius, vec3 color, int type)
{
	this->pos = position;
	this->rad = radius;
	this->color = color;
	this->mat = new Material(type);
}


Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray r, float &t0, float &t1)
{
	//If delta is less than 0 no intersection
	vec3 l = this->pos - r.orig;
	float delta = l.dot(r.dir);
	if (delta < 0)
		return false;

	//If c > than rad^2 no intersection
	float d2 = l.dot(l) - delta * delta;
	if (d2 > this->rad*this->rad)
		return false;

	float thc = sqrt(this->rad*this->rad - d2);
	t0 = delta - thc;
	t1 = delta + thc;

	return true;
}