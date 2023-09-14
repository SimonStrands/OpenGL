#include "Graphics.h"

Graphics::Graphics()
{
	if (!glfwInit()){
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	CreateWindow();
    currentActiveWindow = 0;

	if(glewInit() != GLEW_OK){
        exit(-1);
    }
}

Graphics::~Graphics()
{
	glfwTerminate();
}

void Graphics::UpdateWindows()
{
	for(int i = 0; i < windows.size(); i++){
		if(glfwWindowShouldClose(windows[i])){
			windows.erase(windows.begin() + i);
		}
	}
}

void Graphics::CreateWindow(uint16_t Width, uint16_t Height, std::string Title, bool fullScreen)
{
	//Do more here
	windows.push_back(glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL));
	glfwMakeContextCurrent(windows[windows.size() - 1]);
}

void Graphics::SetActiveWindow(uint8_t ActiveWindow)
{
	currentActiveWindow = ActiveWindow;
}

unsigned int Graphics::GetNrOfWindows()
{
	return (unsigned int)windows.size();
}

GLFWwindow* Graphics::getCurrentActiveWindow()
{
	return windows[currentActiveWindow];
}

GLFWwindow* Graphics::getWindowByIndex(int index)
{
	return windows[index];
}
