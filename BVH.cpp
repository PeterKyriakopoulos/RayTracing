#include <algorithm>
#include "BVH.h"
#include "Log.h"
#include "Stopwatch.h"

struct BVHTraversal {
	uint32_t i; 
	float mint; 
	BVHTraversal() { }
	BVHTraversal(int _i, float _mint) : i(_i), mint(_mint) { }
};

bool BVH::getIntersection(const Ray& ray, IntersectionInfo* intersection, bool occlusion) const {
	intersection->t = 999999999.f;
	intersection->object = NULL;
	float bbhits[4];
	int32_t closer, other;

	BVHTraversal todo[64];
	int32_t stackptr = 0;

	todo[stackptr].i = 0;
	todo[stackptr].mint = -9999999.f;

	while (stackptr >= 0) {
		int ni = todo[stackptr].i;
		float nears = todo[stackptr].mint;
		stackptr--;
		const BVHFlatNode &node(flatTree[ni]);

		if (nears > intersection->t)
			continue;

		if (node.rightOffset == 0) {
			for (uint32_t o = 0; o<node.nPrims; ++o) {
				IntersectionInfo current;

				const Object* obj = (*build_prims)[node.start + o];
				bool hit = obj->getIntersection(ray, &current);

				if (hit) {
					if (occlusion) {
						return true;
					}

					if (current.t < intersection->t) {
						*intersection = current;
					}
				}
			}

		}
		else { 

			bool hitc0 = flatTree[ni + 1].boundBox.intersect(ray, bbhits, bbhits + 1);
			bool hitc1 = flatTree[ni + node.rightOffset].boundBox.intersect(ray, bbhits + 2, bbhits + 3);

			if (hitc0 && hitc1) {

				closer = ni + 1;
				other = ni + node.rightOffset;

				if (bbhits[2] < bbhits[0]) {
					std::swap(bbhits[0], bbhits[2]);
					std::swap(bbhits[1], bbhits[3]);
					std::swap(closer, other);
				}

				todo[++stackptr] = BVHTraversal(other, bbhits[2]);

				todo[++stackptr] = BVHTraversal(closer, bbhits[0]);
			}

			else if (hitc0) {
				todo[++stackptr] = BVHTraversal(ni + 1, bbhits[0]);
			}

			else if (hitc1) {
				todo[++stackptr] = BVHTraversal(ni + node.rightOffset, bbhits[2]);
			}

		}
	}

	if (intersection->object != NULL)
		intersection->hit = ray.orig + ray.dir * intersection->t;

	return intersection->object != NULL;
}

BVH::~BVH() {
	delete[] flatTree;
}

BVH::BVH(std::vector<Object*>* objects, uint32_t leafSize)
	: nNodes(0), nLeafs(0), leafSize(leafSize), build_prims(objects), flatTree(NULL) {
	Stopwatch sw;

	build();

	double constructionTime = sw.read();
	LOG_STAT("Built BVH (%d nodes, with %d leafs) in %d ms", nNodes, nLeafs, (int)(1000 * constructionTime));
}

struct BVHBuildEntry {
	uint32_t parent;
	uint32_t start, end;
};

void BVH::build()
{
	BVHBuildEntry todo[128];
	uint32_t stackptr = 0;
	const uint32_t Untouched = 0xffffffff;
	const uint32_t TouchedTwice = 0xfffffffd;

	todo[stackptr].start = 0;
	todo[stackptr].end = build_prims->size();
	todo[stackptr].parent = 0xfffffffc;
	stackptr++;

	BVHFlatNode node;
	std::vector<BVHFlatNode> buildnodes;
	buildnodes.reserve(build_prims->size() * 2);

	while (stackptr > 0) {
		BVHBuildEntry &bnode(todo[--stackptr]);
		uint32_t start = bnode.start;
		uint32_t end = bnode.end;
		uint32_t nPrims = end - start;

		nNodes++;
		node.start = start;
		node.nPrims = nPrims;
		node.rightOffset = Untouched;

		BoundBox bb((*build_prims)[start]->getBoundBox());
		BoundBox bc((*build_prims)[start]->getCentroid());
		for (uint32_t p = start + 1; p < end; ++p) {
			bb.expand((*build_prims)[p]->getBoundBox());
			bc.expand((*build_prims)[p]->getCentroid());
		}
		node.boundBox = bb;

		if (nPrims <= leafSize) {
			node.rightOffset = 0;
			nLeafs++;
		}

		buildnodes.push_back(node);

		if (bnode.parent != 0xfffffffc) {
			buildnodes[bnode.parent].rightOffset--;

			
			if (buildnodes[bnode.parent].rightOffset == TouchedTwice) {
				buildnodes[bnode.parent].rightOffset = nNodes - 1 - bnode.parent;
			}
		}

		if (node.rightOffset == 0)
			continue;

		uint32_t split_dim = bc.maxDim();

		float split_coord = .5f * (bc.minim[split_dim] + bc.maxim[split_dim]);

		uint32_t mid = start;
		for (uint32_t i = start; i<end; ++i) {
			if ((*build_prims)[i]->getCentroid()[split_dim] < split_coord) {
				std::swap((*build_prims)[i], (*build_prims)[mid]);
				++mid;
			}
		}

		if (mid == start || mid == end) {
			mid = start + (end - start) / 2;
		}

		todo[stackptr].start = mid;
		todo[stackptr].end = end;
		todo[stackptr].parent = nNodes - 1;
		stackptr++;

		todo[stackptr].start = start;
		todo[stackptr].end = mid;
		todo[stackptr].parent = nNodes - 1;
		stackptr++;
	}

	flatTree = new BVHFlatNode[nNodes];
	for (uint32_t n = 0; n<nNodes; ++n)
		flatTree[n] = buildnodes[n];
}