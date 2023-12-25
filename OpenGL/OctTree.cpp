#include "OctTree.h"

OctTree::OctTree():
	depth(0)
{}

OctTree::OctTree(uint8_t depth) :
	depth(depth)
{}

void OctTree::init(uint8_t depth)
{
	this->depth = depth;
}

void OctTree::inseartBlock(const uint16_t& blockid, glm::vec3 localPos, glm::vec3 mid)
{
	if (depth == 0)
	{
		this->blockid = blockid;
	}
	else 
	{
		if (localPos.y > mid.y) {
			mid.y += (float)depth / 2;
			if (localPos.x > mid.x) {
				mid.x += (float)depth / 2;
				if (localPos.z > mid.z) {	
					mid.z += (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 0);
				}
				else {
					mid.z -= (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 1);
				}
			}
			else {
				mid.x -= (float)depth / 2;
				if (localPos.z > mid.z) {
					mid.z += (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 2);
				}
				else {
					mid.z -= (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 3);
				}
			}
		}
		else 
		{
			mid.y -= (float)depth / 2;
			if (localPos.x > mid.x) {
				mid.x += (float)depth / 2;
				if (localPos.z > mid.z) {
					mid.z += (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 4);
				}
				else {
					mid.z -= (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 5);
				}
			}
			else {
				mid.x -= (float)depth / 2;
				if (localPos.z > mid.z) {
					mid.z += (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 6);
				}
				else {
					mid.z -= (float)depth / 2;
					inseartBlock2(blockid, localPos, mid, 7);
				}
			}
		}

	}

	//Chat gpt should try before use
	//int index = 0;
	//
	//if (localPos.y > mid.y) {
	//	index += 1;
	//}
	//
	//if (localPos.x > mid.x) {
	//	index += 2;
	//}
	//
	//if (localPos.z > mid.z) {
	//	index += 4;
	//}
	//
	//inseartBlock2(blockid, localPos, mid, index);
}

void OctTree::removeBlock(glm::vec3 localPos)
{
	//havn't implemented
}

const uint8_t OctTree::getDepth()
{
	return this->depth;
}

void OctTree::render(std::vector<glm::vec4> transformRender, uint32_t& current)
{
}

void OctTree::inseartBlock2(const uint16_t& blockid, glm::vec3 localPos, glm::vec3 mid, int index)
{
	if (leafs[index] == nullptr) {
		leafs[index] = new OctTree(depth - 1);
	}
	leafs[index]->inseartBlock(blockid, localPos, glm::vec3(mid.x, mid.y, mid.z));
}

OctTreeHeader::OctTreeHeader()
{
}

OctTreeHeader::OctTreeHeader(uint8_t depth)
{
	octTree.init(depth);
}

void OctTreeHeader::init(uint8_t depth)
{
	octTree.init(depth);
}

void OctTreeHeader::inseartBlock(const uint16_t& blockid, glm::vec3 localPos, glm::vec3 mid)
{
	localPos -= position;
	if (abs(localPos.x) > octTree.getDepth() ||
		abs(localPos.y) > octTree.getDepth() ||
		abs(localPos.z) > octTree.getDepth()) {
		std::cout << "error : outside the octree" << std::endl;
		return;
	}
	octTree.inseartBlock(blockid, localPos, glm::vec3(0, 0, 0));
}

void OctTreeHeader::removeBlock(glm::vec3 localPos)
{
}

void OctTreeHeader::render(std::vector<glm::vec4> transformRender, uint32_t& current)
{
}
