#include "precomp.h"
#include "Sphere.h"


Sphere::Sphere(vec3 position, float radius)
{
	this->pos = position;
	this->rad = radius;
}


Sphere::~Sphere()
{
}

bool Sphere::Intersect(ray r)
{

}