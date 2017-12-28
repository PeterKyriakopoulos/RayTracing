#ifndef Object_h_
#define Object_h_

#include "IntersectionInfo.h"
#include "Ray.h"
#include "BoundBox.h"

struct Object {
	virtual bool getIntersection(const Ray& ray,IntersectionInfo* intersection)
		const = 0;

	virtual vec3 getNormal(const IntersectionInfo& I) const = 0;
	//changing this to the following also stops an error, but again, im not sure if it actually works
	//virtual BoundBox getBoundBox() const = 0;
	virtual vec3 getBoundBox() const = 0;

	virtual vec3 getCentroid() const = 0;
};

#endif