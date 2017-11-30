#include "precomp.h"
#include "Ray.h"


Ray::Ray(vec3 direction, vec3 origin)
{
	this->dir = direction;
	this->orig = origin;
}


Ray::~Ray()
{
}

