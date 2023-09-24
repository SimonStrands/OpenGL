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
	void setBasicDefaultVariables(DefaultVariableToScene& basic);
	void setResourceManager(ResourceManager* rm);
	void setMouseandKeyboard(Mouse* mouse, Keyboard* keyboard);
private:
	void switchScene(const int sceneID);
	DefaultVariableToScene* basic;
	Scene* currentScene;
	Scene* nextScene;
};
