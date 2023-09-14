#pragma once
#include "Scene.h"
#include "Player.h"

class TestScene : public Scene{
public:
	TestScene();
	virtual ~TestScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:
	GameObject* test;
	GameObject* Sponza;
	GameObject* player;
	Camera cam;
};
