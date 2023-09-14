#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Mouse.h"

enum SceneHandlerCalls{
	NOTHING,
	SWITCH_SCENE,
};
enum SceneID{
	S_TestScene = 0,
};


class Scene{
public:
	Scene();
	virtual ~Scene();
	virtual void init();
	virtual SceneHandlerCalls update(float dt) = 0;
	virtual void render() = 0;
public:
	//FROM ENGINE TO SCENE
	void setResourceManager(ResourceManager *rm);
	void setMouseAndKeyboard(Mouse* mouse, Keyboard* keyboard);
	//FROM SCENE TO ENGINE
	const int getNewSceneID();
protected:
	void switchScene(int sceneID);
	ResourceManager* rm;
	Mouse* mouse;
	Keyboard* keyboard;
private:
	int newSceneID;
};