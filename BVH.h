#pragma once

#include "precomp.h"
#include "BoundBox.h"
#include "Ray.h"

struct BVHFlatNode 
{
	BoundBox boundBox;
	uint32_t start, numPrims, rightOff;
};

class BVH
{
	uint32_t numNodes, numLeafs, leafSize;
	std::vector<Object*>* build_prims;


	void build();

	BVHFlatNode *flatTree;

	public:
	BVH(std::vector<Object*>* objects, uint32_t leafSize = 4);
	bool getIntersection(const Ray &r, IntersectionInfo *intersection, bool occlusion) const;

	~BVH();
};

