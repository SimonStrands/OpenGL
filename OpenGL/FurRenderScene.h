#pragma once
#include "Scene.h"
#include "Player.h"

class FurRenderScene : public Scene
{
public:
	FurRenderScene();
	virtual ~FurRenderScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:
	GameObject* FurPlane;
	GameObject* plane2;
	GameObject* player;
	std::vector<Light*> l;
};