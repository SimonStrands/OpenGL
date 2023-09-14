#pragma once
#include <glm.hpp>

//simple vertex
struct SimpleVertex{
	glm::vec3 position;
};

//Vertex with UV
struct Vertex{
	Vertex(glm::vec3 pos, glm::vec3 normals, glm::vec2 UV):
		m_position(pos), m_normals(normals), m_texChoords(UV)
	{
	}
	glm::vec3 m_position;
	glm::vec3 m_normals;
	glm::vec2 m_texChoords;
	//should I need tangents?
};