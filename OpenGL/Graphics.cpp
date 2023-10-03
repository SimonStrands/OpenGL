#include "Graphics.h"
#include <iostream>

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

	setUpImGui();
	setUpBuffers();
}

Graphics::~Graphics()
{
	glfwTerminate();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool Graphics::UpdateWindows()
{
	for(int i = 0; i < windows.size(); i++){
		if(glfwWindowShouldClose(windows[i])){
			windows.erase(windows.begin() + i);
		}
	}
	return windows.size() < 1;
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

void Graphics::enableWireframeMode(bool enable)
{
	if(enable){
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
	else{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
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

void Graphics::setUpImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); 
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DisplaySize = ImVec2(getWindowCurrentWH().x, getWindowCurrentWH().y);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	if(!ImGui_ImplGlfw_InitForOpenGL(windows[currentActiveWindow], true)){
		std::cout << "error with glfw" << std::endl;
	}
	if(!ImGui_ImplOpenGL3_Init("#version 330")){
		std::cout << "version" << std::endl;
	}
}

void Graphics::setUpBuffers()
{
	BoneConstantBuffer zeroData;
	uniformBuffers.insert(std::pair("SkeletalPose", CreateUniformBuffer(zeroData)));
	//make one for transform also
	
}

unsigned int Graphics::getUniformBuffer(std::string bufferName)
{
	return uniformBuffers[bufferName];
}