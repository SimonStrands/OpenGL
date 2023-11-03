#pragma once
#include "Scene.h"
#include "Player.h"
#include "TestBeahvior.h"

class TestScene : public Scene{
public:
	TestScene();
	virtual ~TestScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:
	GameObject* Plane1;
	GameObject* Plane2;
	GameObject* Dancer;
	GameObject* Sponza;

	GameObject* Sun;
	GameObject* Sun2;

	GameObject* player;
	std::vector<Light*> l;
};
