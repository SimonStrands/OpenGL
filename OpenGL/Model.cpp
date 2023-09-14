#include "Model.h"

Model::Model()
{
    TransformBuffer = CreateUniformBuffer(Transform().toMat4());
}

std::vector<Mesh>& Model::getMeshes()
{
    return meshes;
}

void Model::DirectRender()
{
    for(int i = 0; i < meshes.size(); i++){
		GLTest(glBindVertexArray(meshes[i].m_vertexarray));
		GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshes[i].m_indeciesBuffer));
        GLTest(glDrawElements(GL_TRIANGLES, meshes[i].m_nrOfIndecies, GL_UNSIGNED_INT, nullptr));
	}
}

void Model::setTransform(Transform transform)
{
    UpdateUniformBuffer(glm::transpose(transform.toMat4()), TransformBuffer);
}

Mesh::Mesh()
{
}


Mesh::Mesh(
    unsigned int materialIndex, 
    unsigned int nrOfVertecies,
    unsigned int vertexBuffer, 
    unsigned int nrOfIndecies, 
    unsigned int indeciesBuffer,
    unsigned int vertexArray
):
    m_materialIndex(materialIndex),
    m_nrOfVertecies(nrOfVertecies),
    m_vertexBuffer(vertexBuffer),
    m_nrOfIndecies(nrOfIndecies),
    m_indeciesBuffer(indeciesBuffer),
    m_vertexarray(vertexArray)
{
}

