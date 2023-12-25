#pragma once
#include "ShaderHandler.h"
//#include "ErrorHelper.h"

class DrawQuad
{
public:
	DrawQuad(ResourceManager* rm, ShaderHandler* sh);
	void render();
	uint32_t m_texture;
private:
	ResourceManager* rm;
	ShaderHandler* sh;

	uint32_t VAO;
	uint32_t VBO;
	uint32_t indecies;
};