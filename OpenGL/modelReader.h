#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.h"

class Model;
class Mesh;
class AnimatedModel;

enum VerteciesType{
	animationVertecies,
	normalVertecies
};

struct EngineTextureSave{
	std::string fileName;
	MaterialFlags TextureType;
};

//load Model from fbx, obj and so forth
Mesh loadMeshFromFile(const aiMesh* pMesh);
Model* loadModelFromFile(const std::string& modelFile, ResourceManager* rm);


Mesh loadMeshFromEngine(const aiMesh* pMesh);
Model* loadModelFromEngine(const std::string& modelFile, ResourceManager* rm);

void createModelToEngine(
	std::vector<Vertex> vertecies,
	std::vector<uint32_t> indecies,
	std::vector<EngineTextureSave> textures
	);