#pragma once
#include "Behavior.h"
#include "Camera.h"
#include "Transform.h"
#include "Mouse.h"

class Player : public Behavior{
public:
	Player();
	void init();
	void update(float dt);
private:
	void moveInDirection(float speed);
	Camera* cam;
	Transform* transform;
	Mouse* mouse;
	Keyboard* keyboard;
	int pressDir = 0;
};