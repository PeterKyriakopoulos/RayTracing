#include "precomp.h"
#include "Camera.h"


Camera::Camera(vec3 position, vec3 direction)
{
	this->dir = direction;
	this->pos = position;
}


Camera::~Camera()
{
}

