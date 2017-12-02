#include "precomp.h"
#include "Camera.h"


Camera::Camera(vec3 position, vec3 direction, float fov)
{
	this->dir = direction;
	this->pos = position;
	this->fov = fov;
}


Camera::~Camera()
{
}

