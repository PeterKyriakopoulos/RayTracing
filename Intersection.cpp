#include "precomp.h"
#include "Intersection.h"

Intersection::Intersection(const Ray *r, const Object *object, const float rayT) : r(r), object(object), rayT(rayT) 
{
}

Intersection::Intersection() : r(0), object(0), rayT(-1) 
{
}

