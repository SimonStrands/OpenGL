#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Graphics{
public:
	Graphics();
	virtual ~Graphics();
	void UpdateWindows();
	void CreateWindow(uint16_t Width = 640, uint16_t Height = 480, std::string Title = "", bool fullScreen = false);
	void SetActiveWindow(uint8_t ActiveWindow);
	unsigned int GetNrOfWindows();
	GLFWwindow* getCurrentActiveWindow();
	GLFWwindow* getWindowByIndex(int index);
private:
	uint8_t currentActiveWindow;
	std::vector<GLFWwindow*> windows;
};