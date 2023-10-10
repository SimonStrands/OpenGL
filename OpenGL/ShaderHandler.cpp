#include "ShaderHandler.h"

ShaderHandler::ShaderHandler(ResourceManager* rm)
{
	this->rm = rm;
}

ShaderHandler::~ShaderHandler()
{
}

void ShaderHandler::setCurrentshader(uint32_t shader)
{
	if(currentShaderProgram != shader){
		GLTest(glUseProgram(shader));
	}
}

void ShaderHandler::setCurrentshader(const std::string& shader)
{
	if(currentShaderProgram != rm->getShaderProgram(shader)){
		GLTest(glUseProgram(rm->getShaderProgram(shader)));
	}
}

void ShaderHandler::AddBuffer(const std::string& buffername, const Buffer buffer)
{
	buffers.insert(std::pair(buffername, buffer));
}
