#include "precomp.h"
#include "PointLight.h"

PointLight::PointLight(const vec3 &position, const float intensity, const vec3 &color, const vec3 &attenuationFactors) : position(position), intensity(intensity) , color(color), a(attenuationFactors.x), b(attenuationFactors.y), c(attenuationFactors.z)
{
}


PointLight::~PointLight()
{
}

const vec3 PointLight::getLightVector(const vec3 &point) const 
{
	return normalize(position - point);
}

const vec3 PointLight::getColorAndIntensity(const vec3 &point) const 
{
	vec3 dist = position - point;
	float sqDist = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);

	vec3 temp = color*intensity;
	temp.x /= (4.0f * PI * sqDist);
	temp.y /= (4.0f * PI * sqDist);
	temp.z /= (4.0f * PI * sqDist);

	return temp;
}

float PointLight::distanceToPoint(const vec3 &point) const 
{
	vec3 dist = position - point;
	float sqDist = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;

	return sqrt(sqDist);
}
