#pragma once
#include "template.h"

class Camera
{
public:
	Camera(vec3 position, vec3 direction, float fov);
	~Camera();

	vec3 pos;
	vec3 dir;
	float fov;

	//Variables for checking the movement
	bool holdingForward;
	bool holdingBackward;
	bool holdingLeftStrafe;
	bool holdingRightStrafe;


};

