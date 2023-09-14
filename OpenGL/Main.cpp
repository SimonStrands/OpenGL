//#define TUT 

#ifdef TUT
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include "LoadShaders.h"
#include "ErrorHelper.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        return -1;
    }

    float position[12] = {
        0.0f,0.0f,0.5f,
        0.0f,0.5f,0.5f,
        0.5f,0.5f,0.5f,
        0.5f,0.0f,0.5f
    };

    unsigned int indecies[] = {
        0,1,2,
        2,3,0
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, position, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    unsigned int indeciesBuffer;
    glGenBuffers(1, &indeciesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indeciesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indecies, GL_STATIC_DRAW);

    unsigned int vertexShader, pixelShader;
    if(!loadVShader("BasicVertexShader.vert", vertexShader)){
        std::cout << "error" << std::endl;
    }
    if(!loadPShader("BasicPixelShader.frag", pixelShader)){
        std::cout << "error" << std::endl;
    }
    unsigned int shaderProgram = attachShaders(vertexShader, pixelShader);

    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLTest(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
#else
#include "App.h"
int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    App app;
    app.Run();
    return 0;
}

#endif // TUT

