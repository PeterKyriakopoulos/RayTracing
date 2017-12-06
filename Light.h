#pragma once
class Light
{
public:

	Light(const float intensity, const vec3 &color);
	virtual const vec3 getLightVector(const vec3 &point) const = 0;
	virtual const vec3 getColorAndIntensity(const vec3 &point) const = 0;
	virtual float distanceToPoint(const vec3 &point) const = 0;

	const vec3 color;
	const float intensity;
};

