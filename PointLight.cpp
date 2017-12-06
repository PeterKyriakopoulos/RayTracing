#include "precomp.h"
#include "PointLight.h"

PointLight::PointLight(const vec3 & position, const float intensity, const vec3 & color, const vec3 & attenuationFactors) : pos(position), Light(intensity, color), a(attenuationFactors.x), b(attenuationFactors.y), c(attenuationFactors.z)
{
}

const vec3 PointLight::getLightVector(const vec3 & point) const
{
	vec3 lightVec = pos - point;
	lightVec.normalize();

	return lightVec;
}

const vec3 PointLight::getColorAndIntensity(const vec3 & point) const
{
	vec3 dist = pos - point;
	float sqDist = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;
	
	vec3 lightCol = color * intensity;
	lightCol.x /= (4.0f * PI * sqDist);
	lightCol.y /= (4.0f * PI * sqDist);
	lightCol.z /= (4.0f * PI * sqDist);

	return lightCol;
}

float PointLight::distanceToPoint(const vec3 & point) const
{
	vec3 dist = pos - point;
	float sqDist = dist.x * dist.x + dist.y * dist.y + dist.z * dist.z;

	return sqrt(sqDist);
}
