#pragma once
#include "Scene.h"
#include "TestScene.h"

class SceneHandler{
public:
	SceneHandler(Scene* StartScene);
	virtual ~SceneHandler();
	void Update(float dt);
	void sceneInit();
	void Render();
	void setResourceManager(ResourceManager* rm);
	void setMouseandKeyboard(Mouse* mouse, Keyboard* keyboard);
private:
	void switchScene(const int sceneID);
	ResourceManager* rm;
	Mouse* mouse;
	Keyboard* keyboard;
	Scene* currentScene;
	Scene* nextScene;
};
