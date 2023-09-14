#pragma once
#include "Defines.h"
#include "Graphics.h"
#include "SceneHandler.h"
#include "DeltaTime.h"


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
	Mouse* mouse;
	Keyboard* keyboard;
	ResourceManager* rm;
	DeltaTime dt;
	//renderer
};
