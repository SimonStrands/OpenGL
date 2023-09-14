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
	void moveInDirection(glm::vec3 dir);
	Camera* cam;
	Transform* transform;
	Mouse* mouse;
	Keyboard* keyboard;
};