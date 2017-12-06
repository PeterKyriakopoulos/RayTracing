#pragma once
#include "template.h"
#include "Ray.h"
#include "Material.h"
#include "Object.h"
#include "PointLight.h"
#include <vector>


class Sphere
{
public:
	Sphere(vec3 position, float radius, vec3 color, int type, vec3 emColor);
	~Sphere();
	bool intersect(Ray &r, float &t);
	void getData(vec3 &posHit, vec3 &normHit);
	void traceRay(Ray r, vector<Sphere> &spheres, Sphere *&sphere, float &t);
	vec3 getLighting(vector<PointLight> &lights, vector<Sphere>& spheres, vec3 posHit, vec3 normHit, float bias);

	vec3 pos, color, emColor;
	float rad;
	Material *mat;
};

