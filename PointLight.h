#pragma once
#include "template.h"

class PointLight
{
public:
	PointLight(const vec3 &position, const float intensity, const vec3 &color, const vec3 &attenuationFactors = vec3(0, 1, 1));
	~PointLight();

	const vec3 getLightVector(const vec3 &point) const;
	const vec3 getColorAndIntensity(const vec3 &point) const;
	float distanceToPoint(const vec3 &point) const;

	const vec3 position;
	const vec3 color;
	float intensity;
	float a, b, c;
};
