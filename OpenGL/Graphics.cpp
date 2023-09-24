#include "Graphics.h"

Graphics::Graphics()
{
	if (!glfwInit()){
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glEnable(GL_CULL_FACE);  
	glCullFace(GL_BACK);  

	CreateWindow(1200, 800);
    currentActiveWindow = 0;

	if(glewInit() != GLEW_OK){
        exit(-1);
    }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);  
	glFrontFace(GL_CCW);
	vSynced = true;
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
	WindowWH.push_back(glm::vec2(Width, Height));
	windows.push_back(glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL));
	glfwMakeContextCurrent(windows[windows.size() - 1]);
}

void Graphics::SetActiveWindow(uint8_t ActiveWindow)
{
	currentActiveWindow = ActiveWindow;
}

void Graphics::vSync(bool enable)
{
	if(enable){
		glfwSwapInterval(1);
		vSynced = true;
	}
	else{
		glfwSwapInterval(0);
		vSynced = false;
	}
}

bool Graphics::isVsynced() const
{
	return vSynced;
}

void Graphics::setDefaultViewPort()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, WindowWH[currentActiveWindow].x, WindowWH[currentActiveWindow].y);
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

glm::vec2 Graphics::getWindowCurrentWH() const
{
	return WindowWH[currentActiveWindow];
}

glm::vec2 Graphics::getWindowByIndexWH(int index) const
{
	return WindowWH[index];
}
