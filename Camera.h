#pragma once
#include "template.h"

class Camera
{
public:
	Camera(vec3 position, vec3 direction);
	~Camera();

	vec3 pos;
	vec3 dir;
	float FOV;
};

