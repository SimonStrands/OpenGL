#include "SceneHandler.h"

SceneHandler::SceneHandler(Scene* StartScene):
	currentScene(StartScene)
{
}

SceneHandler::~SceneHandler()
{
	delete currentScene;
}

void SceneHandler::Update(float dt)
{
	currentScene->update(dt);
}

void SceneHandler::sceneInit()
{
	currentScene->init();
}

void SceneHandler::Render()
{
	currentScene->render();
}

void SceneHandler::setResourceManager(ResourceManager* rm)
{
	this->rm = rm;
	currentScene->setResourceManager(rm);
}

void SceneHandler::setMouseandKeyboard(Mouse* mouse, Keyboard* keyboard)
{
	this->mouse = mouse;
	this->keyboard = keyboard;

	currentScene->setMouseAndKeyboard(mouse, keyboard);
}

void SceneHandler::switchScene(const int sceneID)
{
	
	switch (sceneID)
	{
	case S_TestScene:
		nextScene = new TestScene();
		break;
	default:
		break;
	}
	delete currentScene;
	currentScene = nextScene;
	currentScene->setResourceManager(rm);
	currentScene->setMouseAndKeyboard(mouse, keyboard);
	currentScene->init();
}

