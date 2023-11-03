#pragma once
#include "Scene.h"
#include "Player.h"

class PerformanceScene : public Scene{
public:
	PerformanceScene();
	~PerformanceScene();

	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:

};