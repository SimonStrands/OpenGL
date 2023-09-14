#pragma once
#include "Material.h"
#include <vector>
#include "ErrorHelper.h"
#include "Transform.h"
#include "BufferCreator.h"

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
	void DirectRender();
	void setTransform(Transform transform);
private:
	unsigned int TransformBuffer;
	std::vector<Mesh> meshes;
};

