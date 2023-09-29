#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "ResourceManager.h"

class Model;
class Mesh;

Mesh loadMesh(const aiMesh* pMesh);
Mesh loadAnimationMesh(const aiMesh* pMesh);
Model* loadModel(const std::string& modelFile, ResourceManager* rm);

