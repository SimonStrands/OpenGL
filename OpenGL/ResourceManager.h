#pragma once
#include "ImageReader.h"
#include "BufferCreator.h"
#include "LoadShaders.h"
#include "Vertex.h"
#include "Material.h"
#include "Model.h"
#include <map>
#include <string>
#include <iostream>

class ResourceManager{
public:
	ResourceManager();
	virtual ~ResourceManager();
	Model* getModel(const std::string& FileName);

	unsigned int getShader(const std::string& ShaderFile);
	unsigned int getShaderProgram(const std::string& ShaderProgram);
	unsigned int getTexture(const std::string& FileName);

private:
	std::map<std::string, Model*> Models; 
	std::map<std::string, unsigned int> Shaders; 
	std::map<std::string, unsigned int> ShaderProgram; 
	std::map<std::string, unsigned int> Textures;
	void loadDef();
};
