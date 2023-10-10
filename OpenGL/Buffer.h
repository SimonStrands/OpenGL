#pragma once
#include "BufferCreator.h"

class Buffer{
public:
	Buffer();
	uint32_t& Get();
	//create different Buffers
	void CreateVertexArray_();
	template <typename T>
	void CreateVertexBuffer_(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
		CreateVertexBuffer(vertecies, type);
	}
	template <typename T>
	void CreateAnimationVertexBuffer_(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
		CreateAnimationVertexBuffer(vertecies, type);
	}
	void CreateIndeciesBuffer_(std::vector<uint32_t>& vertecies);


	template <typename T>
	void UpdateData(const T& data){
		UpdateUniformBuffer(data, this->buffer);
	}
protected:
	uint32_t buffer;
	
};

class UniformBuffer : public Buffer{
public:
	//if current program is bind no need to set the program
	template <typename T>
	UniformBuffer(T data, const std::string& uniformName, uint16_t bindngIndex, int program = -1){
		CreateUniformBuffer(data);
		this->bindingIndex = bindngIndex;
		blockIndex = -1;

		if(program == -1){
			glGetIntegerv(GL_CURRENT_PROGRAM, &program);
		}
		blockIndex = glGetUniformBlockIndex(program, uniformName.c_str());
	}

	template <typename T>
	void UpdateData(const T& data){
		UpdateUniformBuffer(data, this->buffer);
	}
	void setUniform(const uint32_t currentProgram);
private:
	uint16_t bindingIndex;
	GLint blockIndex;
};

class SSBOBuffer : public Buffer{
public:
	template <typename T>
	SSBOBuffer(const T& data, const uint32_t bindingIndex){
		this->buffer = CreateSSBO(data, bindingIndex);
	}
	template <typename T>
	void UpdateData(const T& data){
		UpdateSSBO(data, this->buffer);
	}
	void setSSBO(const uint32_t currentProgram);
private:
	GLint blockIndex;
};