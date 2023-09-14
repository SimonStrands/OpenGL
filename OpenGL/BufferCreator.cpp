#include "BufferCreator.h"

unsigned int CreateVertexArray()
{
    unsigned int buffer = 0;

    GLTest(glGenVertexArrays(1, &buffer));
    GLTest(glBindVertexArray(buffer));

    return buffer;
}

unsigned int CreateIndeciesBuffer(std::vector<unsigned int>& vertecies)
{
	unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW);
    return buffer;
}

void setUniform(std::string uniformName, const unsigned int uniformBuffer)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);
    GLint v;
	glGetIntegerv(GL_CURRENT_PROGRAM, &v);
    
    GLuint bindingIndex = 0;
	GLuint blockIndex = glGetUniformBlockIndex(v, uniformName.c_str());
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);
	glUniformBlockBinding(v, blockIndex, bindingIndex);
}
