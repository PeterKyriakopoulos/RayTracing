#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const vec3 &position, const float intensity, const vec3 &color, const vec3 &attenuationFactors = vec3(0, 1, 1));
	const vec3 getLightVector(const vec3 &point) const;
	const vec3 getColorAndIntensity(const vec3 &point) const;
	float distanceToPoint(const vec3 &point) const;

	vec3 pos;
	float a, b, c;
};

