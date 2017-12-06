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

vec3 Plane::getLighting(vector<PointLight> &lights, vector<Plane>& planes, vec3 posHit, vec3 normHit, float bias)
{
	vec3 pixCol = 0;

	for (unsigned j = 0; j < lights.size(); j++)
	{
		vec3 lightDir = posHit - lights[j].position;
		lightDir.normalize();
		vec3 lightOrig = posHit + normHit * bias;
		Ray *lightRay = new Ray(lightDir, lightOrig);
		vec3 transm = vec3(1);

		for (unsigned i = 0; i < planes.size(); i++)
		{
			float t;

			if (planes[i].intersect(*lightRay, t))
			{

				transm = vec3(0);
				break;
			}
		}

		pixCol += this->color * lights[j].color * std::_Max_value(float(0), normHit.dot(-lightDir));	
	}

	return pixCol;
}

