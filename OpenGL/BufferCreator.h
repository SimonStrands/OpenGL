#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "ErrorHelper.h"

template <typename T>
unsigned int CreateVertexBuffer(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	unsigned int buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    
    GLTest(glEnableVertexAttribArray(0));
    int nrOfThings = sizeof(T) / sizeof(float);
    //is 3 wrong need to check later
    GLTest(glVertexAttribPointer(0, 3, type, GL_FALSE, sizeof(T), 0));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));

    return buffer;
}

unsigned int CreateVertexArray();

unsigned int CreateIndeciesBuffer(std::vector<unsigned int>& vertecies);

template <typename T>
unsigned int CreateUniformBuffer(T data){
    unsigned int UB;
    GLTest(glGenBuffers(1, &UB));
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, UB));
    GLTest(glBufferData(GL_UNIFORM_BUFFER, sizeof(T), NULL, GL_DYNAMIC_DRAW));
    return UB;
}

template <typename T>
void UpdateUniformBuffer(const T data, unsigned int buff){
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, buff));
    void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    if(ptr){
        memcpy(ptr, &data, sizeof(data));
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void setUniform(std::string uniformName, const unsigned int uniformBuffer);