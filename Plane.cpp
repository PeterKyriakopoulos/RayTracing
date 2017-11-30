#include "precomp.h"
#include "Plane.h"
#include "Ray.h"
#include "Material.h"


Plane::Plane(vec3 position, vec3 normal, vec3 color, int type)
{
	this->pos = position;
	this->norm = normal;
	this->color = color;
	this->mat = new Material(type);
}


Plane::~Plane()
{
}

//Check if ray intersects plane
bool Plane::intersect(Ray r, float &t)
{
	float den = this->norm.dot(r.dir);
	if (den > 1e-6)
	{
		vec3 l = this->pos - r.orig;
		t = l.dot(this->norm) / den;
	
		return (t >= 0);
	}

	return false;
}