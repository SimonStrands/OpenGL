#include "LoadShaders.h"

void tester()
{
	std::cout << "test" << std::endl;
}

bool readShader(const std::string& name, std::string& shaderData)
{
	std::ifstream reader;
	reader.open(Path + name, std::ios::binary | std::ios::ate);

	if (!reader.is_open())
	{
		printf("cannot open vertex file\n");
		return false;
	}

	reader.seekg(0, std::ios::end);
	shaderData.reserve(static_cast<unsigned int>(reader.tellg()));
	reader.seekg(0, std::ios::beg);

	shaderData.assign((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	reader.close();

	return true;
}

void readShaderError(unsigned int shader, unsigned int type)
{
	int lenght;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &lenght);
    char* message = (char*)alloca(lenght * sizeof(char));
    glGetShaderInfoLog(shader, lenght, &lenght, message);
    
    std::cout << "ERROR: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << message << std::endl;

    glDeleteShader(shader);

}

bool loadVShader(const std::string& name, unsigned int& vertexShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	vertexShader = glCreateShader(0x8B31);
	const char* src = shaderData.c_str();
	glShaderSource(vertexShader, 1, &src, nullptr);
	glCompileShader(vertexShader);
	int res;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(vertexShader, 0x8B31);
		return false;
	}
	return true;
}

bool loadPShader(const std::string& name, unsigned int& pixelShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	pixelShader = glCreateShader(0x8B30);
	const char* src = shaderData.c_str();
	glShaderSource(pixelShader, 1, &src, nullptr);
	glCompileShader(pixelShader);
	int res;
    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(pixelShader, 0x8B30);
		return false;
	}
	return true;

}

unsigned int attachShaders(unsigned int vertexShader, unsigned int pixelShader)
{
	unsigned int p = glCreateProgram();
	glAttachShader(p, vertexShader);
    glAttachShader(p, pixelShader);
    glLinkProgram(p);
    glValidateProgram(p);

	//should probably not do this here later
    glDeleteShader(vertexShader);
    glDeleteShader(pixelShader);

	return p;
}
