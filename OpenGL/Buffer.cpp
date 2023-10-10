#include "Buffer.h"

Buffer::Buffer():
    buffer(0)
{
}

uint32_t& Buffer::Get()
{
    return this->buffer;
}

void Buffer::CreateVertexArray_()
{
    this->buffer = CreateVertexArray();
}

void Buffer::CreateIndeciesBuffer_(std::vector<uint32_t>& vertecies)
{
    this->buffer = CreateIndeciesBuffer(vertecies);
}

void UniformBuffer::setUniform(const uint32_t currentProgram)
{
    GLTest(glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, this->buffer));
	GLTest(glUniformBlockBinding(currentProgram, blockIndex, bindingIndex));
}

void SSBOBuffer::setSSBO(const uint32_t currentProgram)
{
    uint32_t block_index = 0;
    block_index = glGetProgramResourceIndex(currentProgram, GL_SHADER_STORAGE_BLOCK, "shader_data");
}
