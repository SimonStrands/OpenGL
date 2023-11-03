#pragma once
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "../OpenGL/Material.h"
#include "../OpenGL/Vertex.h"
#include <fstream>

enum VerteciesType{
	animationVertecies,
	normalVertecies
};

struct MaterialSave{
    MaterialFlags materialFlags;
    std::vector<std::string> fileNames;
    std::vector<MaterialFlags> TextureType;
    float Ns;
    glm::fvec3 Ka;
	glm::fvec3 Kd;
	glm::fvec3 Ks;
	glm::fvec3 Ke;
	float Ni;
	float d;
	
	bool tessellate;
	float tessellationLevel;
};

template <typename T>
void writeVectorFromFile(std::ofstream& file, std::vector<T> vec){
    uint32_t uw = (uint32_t)vec.size();
    file.write((char*)&uw, sizeof(uint32_t));
    file.write((char*)&vec[0], sizeof(T) * uw);
}

bool convert(const std::string& fileName, std::string newName = "");