#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "ErrorHelper.h"

template <typename T>
uint32_t CreateVertexBuffer(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	uint32_t buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    
    GLTest(glEnableVertexAttribArray(0));
    GLTest(glVertexAttribPointer(0, 3, type, GL_FALSE, sizeof(T), 0));
    GLTest(glEnableVertexAttribArray(1));
    GLTest(glVertexAttribPointer(1, 2, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_texChoords)));
    GLTest(glEnableVertexAttribArray(2));
    GLTest(glVertexAttribPointer(2, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_normals)));
    GLTest(glEnableVertexAttribArray(3));
    GLTest(glVertexAttribPointer(3, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_tangent)));
    GLTest(glEnableVertexAttribArray(4));
    GLTest(glVertexAttribPointer(4, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_bitangent)));

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return buffer;
}

template <typename T>
uint32_t CreateAnimationVertexBuffer(std::vector<T>& vertecies, GLenum type = GL_FLOAT){
	uint32_t buffer = 0;
    GLTest(glGenBuffers(1, &buffer));
    GLTest(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLTest(glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertecies.size(), vertecies.data(), GL_STATIC_DRAW));
    
    
    GLTest(glEnableVertexAttribArray(0));
    GLTest(glVertexAttribPointer(0, 3, type, GL_FALSE, sizeof(T), 0));
    GLTest(glEnableVertexAttribArray(1));
    GLTest(glVertexAttribPointer(1, 2, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_texChoords)));
    GLTest(glEnableVertexAttribArray(2));
    GLTest(glVertexAttribPointer(2, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_normals)));
    GLTest(glEnableVertexAttribArray(3));
    GLTest(glVertexAttribPointer(3, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_tangent)));
    GLTest(glEnableVertexAttribArray(4));
    GLTest(glVertexAttribPointer(4, 3, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_bitangent)));
    GLTest(glEnableVertexAttribArray(5));
    GLTest(glVertexAttribPointer(5, 4, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_boneIDs)));
    GLTest(glEnableVertexAttribArray(6));
    GLTest(glVertexAttribPointer(6, 4, type, GL_FALSE, sizeof(T), (void*)offsetof(T, m_boneWeights)));

    GLTest(glBindBuffer(GL_ARRAY_BUFFER, 0));

    return buffer;
}

uint32_t CreateVertexArray();

uint32_t CreateIndeciesBuffer(std::vector<uint32_t>& vertecies);

template <typename T>
uint32_t CreateUniformBuffer(T data){
    uint32_t UB;
    GLTest(glGenBuffers(1, &UB));
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, UB));
    GLTest(glBufferData(GL_UNIFORM_BUFFER, sizeof(T), NULL, GL_DYNAMIC_DRAW));
    return UB;
}

template <typename T>
void UpdateUniformBuffer(const T data, uint32_t buff){
    GLTest(glBindBuffer(GL_UNIFORM_BUFFER, buff));
    void* ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
    if(ptr){
        memcpy(ptr, &data, sizeof(data));
        GLTest(glUnmapBuffer(GL_UNIFORM_BUFFER));
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void setUniform(std::string uniformName, const uint32_t uniformBuffer, GLuint bindingIndex = 0);

void createDepthStencil(uint32_t Width, uint32_t Height, uint32_t &depthBufferFBO, uint32_t &depthBuffer);