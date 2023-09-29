#pragma once
#include "Material.h"
#include <vector>
#include "ErrorHelper.h"
#include "Transform.h"
#include "BufferCreator.h"

struct materialConstBuffer{
    glm::vec4 Ka;//add ni here
    glm::vec4 Kd;//add d here
    glm::vec4 Ks;//ns here as w
    glm::vec4 Ke;//add materials flags here
	void operator=(const Material& m){
		this->Ka = glm::vec4(m.Ka, m.Ni);
		this->Kd = glm::vec4(m.Kd, m.d);
		this->Ks = glm::vec4(m.Ks, m.Ns);
		this->Ke = glm::vec4(m.Ke, m.materialFlags);
	};
};

class Mesh{
public:
	Mesh();
	Mesh(unsigned int materialIndex,
		unsigned int nrOfVertecies,
		unsigned int vertexBuffer,
		unsigned int nrOfIndecies,
		unsigned int indeciesBuffer,
		unsigned int vertexArray
		);
public:
	Material material;
	unsigned int mcb; //materialConstBuffer does not handle textures

	unsigned int m_materialIndex;

	unsigned int m_nrOfVertecies;
	unsigned int m_vertexBuffer;

	unsigned int m_nrOfIndecies;
	unsigned int m_indeciesBuffer;

	unsigned int m_vertexarray;
};

class Model{
public:
	Model();
	std::vector<Mesh> &getMeshes();
	void DirectRender(GLuint Topology = GL_TRIANGLES);
	void DirectRenderShadow();
	void setTransform(Transform transform);
private:
	unsigned int TransformBuffer;
	std::vector<Mesh> meshes;
};

