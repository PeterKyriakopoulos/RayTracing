#pragma once

#include "precomp.h"
#include "BoundBox.h"
#include "Ray.h"

struct BVHFlatNode 
{
	BoundBox boundBox;
	uint32_t start, nPrims, rightOffset;
};

class BVH
{
	uint32_t nNodes, nLeafs, leafSize;
	std::vector<Object*>* build_prims;

	//! Build the BVH tree out of build_prims
	void build();

	// Fast Traversal System
	BVHFlatNode *flatTree;

	public:
	BVH(std::vector<Object*>* objects, uint32_t leafSize = 4);
	bool getIntersection(const Ray &r, IntersectionInfo *intersection, bool occlusion) const;

	~BVH();
};

