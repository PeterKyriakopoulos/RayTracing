#include "precomp.h"
#include "Sphere.h"
#include "Ray.h"


Sphere::Sphere(vec3 position, float radius, vec3 color, int type, vec3 emColor)
{
	this->pos = position;
	this->rad = radius;
	this->color = color;
	this->mat = new Material(type);
	this->emColor = emColor;
}


Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray &r, float &t)
{
	float t0, t1;

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

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) 
	{
		t0 = t1; 
		if (t0 < 0) return false; 
	}

	t = t0;

	return true;
}

void Sphere::getData(vec3 & posHit, vec3 & normHit)
{
	normHit = posHit - this->pos;
	normHit.normalize();
}

void Sphere::traceRay(Ray r, vector<Sphere>& spheres, Sphere *& sphere, float &t)
{
	for (uint i = 0; i < spheres.size(); i++)
	{
		float tnear = std::numeric_limits<float>::infinity();

		if (spheres[i].intersect(r, tnear) && tnear < t)
		{
			sphere = &spheres[i];
			t = tnear;
		}
	}
}

vec3 Sphere::getLighting(vector<Sphere> &spheres, vec3 posHit, vec3 normHit, float bias)
{
	vec3 pixCol = 0;

	for (unsigned j = 0; j < spheres.size(); j++)
	{
		if (spheres[j].emColor.x > 0)
		{
			vec3 transm = 1;
			vec3 lightDir = spheres[j].pos - posHit;
			lightDir.normalize();

			for (unsigned i = 0; i < spheres.size(); i++)
			{
				if (j != i)
				{
					float t0;
					Ray *tempLight = new Ray(lightDir, posHit + normHit * bias);

					if (spheres[i].intersect(*tempLight, t0))
					{
						transm = 0;
						break;
					}
				}
			}
			pixCol += this->color * transm * std::_Max_value(float(0), normHit.dot(lightDir)) * spheres[j].emColor;
		}
	}

	return pixCol;
}







