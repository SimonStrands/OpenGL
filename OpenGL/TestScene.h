#pragma once
#include "Scene.h"
#include "Player.h"
#include "TestBeahvior.h"

#include "RaySphere.h"
#include "DrawQuad.h"


class TestScene : public Scene{
public:
	TestScene();
	virtual ~TestScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:

	GameObject* Sun;
	DrawQuad* dq;

	GameObject* player;
	std::vector<Light*> l;
};
