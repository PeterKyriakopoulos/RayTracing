#ifndef Object_h_
#define Object_h_

#include "IntersectionInfo.h"
#include "Ray.h"
#include "BoundBox.h"

struct Object {
	virtual bool getIntersection(
		const Ray& ray,
		IntersectionInfo* intersection)
		const = 0;

	virtual vec3 getNormal(const IntersectionInfo& I) const = 0;

	virtual BoundBox getBoundBox() const = 0;

	virtual vec3 getCentroid() const = 0;
};

#endif