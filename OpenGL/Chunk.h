#pragma once
#include "OctTree.h"

class Chunk {
public:
	Chunk();
	void render();
private:
#define NrOfOctTrees 3
#define SizeOfOctrees 3
	OctTreeHeader octTrees[NrOfOctTrees];
};