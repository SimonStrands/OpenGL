#pragma once
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Graphics{
public:
	Graphics();
	virtual ~Graphics();
	bool UpdateWindows();
	void CreateWindow(uint16_t Width = 640, uint16_t Height = 480, std::string Title = "", bool fullScreen = false);
	void SetActiveWindow(uint8_t ActiveWindow);
	void vSync(bool enable);
	bool isVsynced()const;
	void setDefaultViewPort();
	unsigned int GetNrOfWindows();
	GLFWwindow* getCurrentActiveWindow();
	GLFWwindow* getWindowByIndex(int index);
	glm::vec2 getWindowCurrentWH() const;
	glm::vec2 getWindowByIndexWH(int index) const;
private:
	void setUpImGui();
private:
	uint8_t currentActiveWindow;
	std::vector<GLFWwindow*> windows;
	std::vector<glm::vec2> WindowWH;
	bool vSynced;
};