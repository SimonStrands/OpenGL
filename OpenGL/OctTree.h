#pragma once
#include "Buffer.h"

class OctTreeHeader {
public:
	OctTreeHeader();
	OctTreeHeader(uint8_t depth);
	void init(uint8_t depth);
	void inseartBlock(const uint16_t& blockid, glm::vec3 position, glm::vec3 mid);
	void removeBlock(glm::vec3 position);//should return something but don't know what
	void render(std::vector<glm::vec4> transformRender, uint32_t& current);
private:
	OctTree octTree;
	glm::vec3 position;
};

class OctTree {
public:
	OctTree();
	OctTree(uint8_t depth);
	void init(uint8_t depth);

	void inseartBlock(const uint16_t& blockid, glm::vec3 localPos, glm::vec3 mid);
	void removeBlock(glm::vec3 localPos);//should return something but don't know what
	const uint8_t getDepth();
	void render(std::vector<glm::vec4> transformRender, uint32_t& current);
private:
	void inseartBlock2(const uint16_t& blockid, glm::vec3 localPos, glm::vec3 mid, int index);
	uint8_t depth;
	uint16_t blockid;
	bool activeBlock;
	OctTree* leafs[8];
	//first 4 top
	//last 4 is bot
	//top left, 
};