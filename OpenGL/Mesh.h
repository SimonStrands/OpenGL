#pragma once
#include "Material.h"

enum class TypeOfMesh {
	Default,
	Animated
};

class Mesh{
public:
	Mesh();
	Mesh(unsigned int materialIndex,
		unsigned int nrOfVertecies,
		unsigned int vertexBuffer,
		unsigned int nrOfIndecies,
		unsigned int indeciesBuffer,
		unsigned int vertexArray,
		TypeOfMesh meshType
		);
	TypeOfMesh GetModelType() const;
public:
	TypeOfMesh typeOfMesh;
	Material material;
	unsigned int mcb; //materialConstBuffer does not handle textures

	unsigned int m_materialIndex;

	unsigned int m_nrOfVertecies;
	unsigned int m_vertexBuffer;

	unsigned int m_nrOfIndecies;
	unsigned int m_indeciesBuffer;

	unsigned int m_vertexarray;
};