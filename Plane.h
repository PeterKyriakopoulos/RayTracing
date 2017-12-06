#pragma once
#include "template.h"
#include "Material.h"
#include "Ray.h"
#include "Object.h"
#include "PointLight.h"
#include <vector>

class Plane
{
public:
	Plane(vec3 position, vec3 normal, vec3 color, int type);
	~Plane();
	bool intersect(Ray &r, float &t);
	void getData(vec3 &posHit, vec3 &normHit);
	void traceRay(Ray r, vector<Plane> &planes, Plane *&plane, float &t);
	vec3 getLighting(vector<PointLight> &lights, vector<Plane>& planes, vec3 posHit, vec3 normHit, float bias);

	vec3 pos, color, norm;
	Material *mat;
};

