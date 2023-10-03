#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.h"

class Model;
class Mesh;
class AnimatedModel;

Mesh loadMesh(const aiMesh* pMesh);
Mesh loadAnimatedMesh(const aiMesh* pMesh, std::map<std::string, glm::mat4>& offsetMatrices);
Model* loadModel(const std::string& modelFile, ResourceManager* rm);