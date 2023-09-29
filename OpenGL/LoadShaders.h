#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
//kinda fucked up here butt idk
#ifdef _DEBUG
#define Path "Shaders/"
#else
#define Path "Shaders/"
#endif

//Just return the data
bool readShader(const std::string& name, std::string &shaderData);

void readShaderError(unsigned int shader, unsigned int type);

bool loadVShader(const std::string& name, unsigned int &vertexShader);

//TESSControlShader
bool loadHShader(const std::string& name, unsigned int &hullShader);

//TESSEvaluationShader
bool loadDShader(const std::string& name, unsigned int &domainShader);

bool loadGShader(const std::string& name, unsigned int &geometryShader);

bool loadPShader(const std::string& name, unsigned int &pixelShader);

unsigned int attachShaders(unsigned int vertexShader, unsigned int pixelShader);

unsigned int attachShaders( unsigned int vertex, unsigned int control, unsigned int evaluation, unsigned int pixel);
