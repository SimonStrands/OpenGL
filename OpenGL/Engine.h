#pragma once
#include "Defines.h"
#include "Graphics.h"
#include "SceneHandler.h"
#include "DeltaTime.h"
#include "ShadowMap.h"
#include "ImGuiManager.h"


class Engine{
public:
	Engine();
	virtual ~Engine();
	void Run();
private:
	//Variables
	bool m_gameOver;
	//Objects
	SceneHandler m_sceneHandler;
	Graphics gfx;
	DeltaTime dt;
	DefaultVariableToScene basicToScene;
	ImGuiManager imGuiManager;
	//renderer
};
