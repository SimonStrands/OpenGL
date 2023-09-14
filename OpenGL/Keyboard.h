#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Keyboard{
public:
	Keyboard(GLFWwindow* wnd);
	bool getKeyDown(unsigned char key);
	bool getKeyDown(int key);
	bool getKeyUp(unsigned char key);
	bool getKeyUp(int key);
private:
	GLFWwindow* wnd;
};