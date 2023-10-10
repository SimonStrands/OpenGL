#pragma once
#include "ResourceManager.h"
#include "ErrorHelper.h"

class ShaderHandler{
public:
	ShaderHandler(ResourceManager* rm);
	virtual ~ShaderHandler();

	void setCurrentshader(uint32_t shader);
	void setCurrentshader(const std::string &shader);

	void AddBuffer(const std::string& buffername, const Buffer buffer);

	template <typename T>
	void updateBuffers(const std::string& buffer, const T& data){
		if(buffers.find(buffer) != buffers.end()){
			buffers[buffer].UpdateData(data);
		}
	}
private:
	std::map<std::string, Buffer> buffers;

	ResourceManager* rm;
	uint32_t currentShaderProgram;
};