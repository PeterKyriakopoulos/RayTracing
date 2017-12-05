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
bool Plane::intersect(Ray &r, float &t)
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

void Plane::getData(vec3 & posHit, vec3 & normHit)
{
	normHit = posHit - this->pos;
	normHit.normalize();
}

void Plane::traceRay(Ray r, vector<Plane>& planes, Plane *& plane, float & t)
{
	for (uint i = 0; i < planes.size(); i++)
	{
		float tnear = std::numeric_limits<float>::infinity();

		if (planes[i].intersect(r, tnear) && tnear < t)
		{
			plane = &planes[i];
			t = tnear;
		}
	}
}

vec3 Plane::getLighting(vector<Sphere> &spheres, vector<Plane>& planes, vec3 posHit, vec3 normHit, float bias)
{
	vec3 pixCol = 0;

	for (unsigned j = 0; j < spheres.size(); j++)
	{
		if (spheres[j].emColor.x > 0)
		{
			vec3 transm = 1;
			vec3 lightDir = spheres[j].pos - posHit;
			lightDir.normalize();

			for (unsigned i = 0; i < planes.size(); i++)
			{
				if (j != i)
				{
					float t0;
					Ray *tempLight = new Ray(lightDir, posHit + normHit * bias);

					if (planes[i].intersect(*tempLight, t0))
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

