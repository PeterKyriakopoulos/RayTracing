#include "precomp.h"
#include "Camera.h"


int posX, posY, posZ;

Camera::Camera(int positionX, int positionY, int positionZ)
{
	posX = positionX;
	posY = positionY;
	posZ = positionZ;
}


Camera::~Camera()
{
}
