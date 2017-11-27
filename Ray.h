#pragma once


class Ray
{
public:
	Ray(vec3 direction, vec3 origin);
	~Ray();	

	vec3 dir;
	vec3 orig;
};

