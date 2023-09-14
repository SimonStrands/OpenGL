#include "Keyboard.h"

Keyboard::Keyboard(GLFWwindow* wnd)
{
	this->wnd = wnd;
}

bool Keyboard::getKeyDown(unsigned char key)
{
	return (glfwGetKey(this->wnd, key) == GLFW_PRESS);
}

bool Keyboard::getKeyDown(int key)
{
	return (glfwGetKey(this->wnd, key) == GLFW_PRESS);
}

bool Keyboard::getKeyUp(unsigned char key)
{
	return (glfwGetKey(this->wnd, key) == GLFW_RELEASE);
}

bool Keyboard::getKeyUp(int key)
{
	return (glfwGetKey(this->wnd, key) == GLFW_RELEASE);
}
