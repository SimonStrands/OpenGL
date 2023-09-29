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

	//create more here later if we need hull, displacement and more
	unsigned int createShaderProgram(const std::string& ShaderProgramName, unsigned int vertex, unsigned int pixel);
	unsigned int createShaderProgram(const std::string& ShaderProgramName, unsigned int vertex, unsigned int control, unsigned int evaluation, unsigned int pixel);

private:
	std::map<std::string, Model*> Models; 
	std::map<std::string, unsigned int> Shaders; 
	std::map<std::string, unsigned int> ShaderProgram; 
	std::map<std::string, unsigned int> Textures;
	void loadDef();
};
