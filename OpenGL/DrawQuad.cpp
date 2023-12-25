#include "DrawQuad.h"

DrawQuad::DrawQuad(ResourceManager* rm, ShaderHandler* sh)
{
	this->rm = rm;
	this->sh = sh;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 800, 800, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

	//m_texture = rm->getTexture("../Textures/Quad.jpg");

	VAO = CreateVertexArray();
	std::vector<Vertex> vertecies;
	vertecies.push_back(Vertex(glm::vec3(-1, -1, 0), glm::vec2(0, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	vertecies.push_back(Vertex(glm::vec3(-1, 1, 0), glm::vec2(0, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	vertecies.push_back(Vertex(glm::vec3(1, -1, 0), glm::vec2(1, 0), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	vertecies.push_back(Vertex(glm::vec3(1, 1, 0), glm::vec2(1, 1), glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	VBO = CreateVertexBuffer(vertecies);
	std::vector<uint32_t> indecie = { 0,1,2,3 };
	indecies = CreateIndeciesBuffer(indecie);

	rm->createShaderProgram("DrawQuad", rm->getShader("DrawQuadVertex.vert"), rm->getShader("DrawQuadFrag.frag"));
}

void DrawQuad::render()
{
	//TODO : disable depth buffer
	sh->setCurrentshader(rm->getShaderProgram("DrawQuad"));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	GLTest(glBindVertexArray(VAO));
	GLTest(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indecies));

	GLTest(glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr));
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
