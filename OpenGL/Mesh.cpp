#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::Mesh(
    unsigned int materialIndex, 
    unsigned int nrOfVertecies,
    unsigned int vertexBuffer, 
    unsigned int nrOfIndecies, 
    unsigned int indeciesBuffer,
    unsigned int vertexArray,
    TypeOfMesh meshType
):
    m_materialIndex(materialIndex),
    m_nrOfVertecies(nrOfVertecies),
    m_vertexBuffer(vertexBuffer),
    m_nrOfIndecies(nrOfIndecies),
    m_indeciesBuffer(indeciesBuffer),
    m_vertexarray(vertexArray),
    typeOfMesh(meshType)
{
}

TypeOfMesh Mesh::GetModelType() const
{
    return this->typeOfMesh;
}
