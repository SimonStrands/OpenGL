#include "Chunk.h"

Chunk::Chunk()
{
	for (int i = 0; i < NrOfOctTrees; i++)
	{
		octTrees[i].init(SizeOfOctrees);
	}
}

void Chunk::render()
{
	for (int i = 0; i < NrOfOctTrees; i++)
	{
		octTrees->render();
	}
}
