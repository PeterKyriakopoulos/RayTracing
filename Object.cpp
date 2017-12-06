#include "precomp.h"
#include "Object.h"


Object::Object(const vec3 &position, const int type, const vec3 &color) : mat(new Material(type)), position(position), color(color)
{
}

Object::Object(const Material *material) : mat(material) 
{
}
