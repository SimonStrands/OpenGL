#include "LoadShaders.h"
#include "ErrorHelper.h"

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
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(vertexShader, 1, &src, nullptr);
	glCompileShader(vertexShader);
	int res;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(vertexShader, GL_VERTEX_SHADER);
		return false;
	}
	return true; 
}

bool loadHShader(const std::string& name, unsigned int& hullShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	
	hullShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(hullShader, 1, &src, nullptr);
	glCompileShader(hullShader);
	int res;
    glGetShaderiv(hullShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(hullShader, GL_TESS_CONTROL_SHADER);
		return false;
	}
	return true; 
}

bool loadDShader(const std::string& name, unsigned int& domainShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	domainShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(domainShader, 1, &src, nullptr);
	glCompileShader(domainShader);
	int res;
    glGetShaderiv(domainShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(domainShader, GL_TESS_EVALUATION_SHADER);
		return false;
	}
	return true;
}

bool loadGShader(const std::string& name, unsigned int& geometryShader)
{
	std::string shaderData;
	if(!readShader(name, shaderData)){
		return false;
	}
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(geometryShader, 1, &src, nullptr);
	glCompileShader(geometryShader);
	int res;
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(geometryShader, GL_GEOMETRY_SHADER);
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
	pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* src = shaderData.c_str();
	glShaderSource(pixelShader, 1, &src, nullptr);
	glCompileShader(pixelShader);
	int res;
    glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &res);
    if(res == GL_FALSE){
		readShaderError(pixelShader, GL_FRAGMENT_SHADER);
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
    //glDeleteShader(vertexShader);
    //glDeleteShader(pixelShader);

	return p;
}

unsigned int attachShaders(unsigned int vertex, unsigned int control, unsigned int evaluation, unsigned int pixel)
{
	unsigned int p = glCreateProgram();
	GLTest(glAttachShader(p, vertex));
	GLTest(glAttachShader(p, pixel));
	GLTest(glAttachShader(p, control));
	GLTest(glAttachShader(p, evaluation));
    GLTest(glLinkProgram(p));
    GLTest(glValidateProgram(p));

	//should probably not do this here later
    //glDeleteShader(vertexShader);
    //glDeleteShader(pixelShader);

	return p;
}
