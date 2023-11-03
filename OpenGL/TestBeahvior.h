#pragma once
#include "Behavior.h"
#include "Transform.h"

class TestBehavior : public Behavior{
public:
	TestBehavior();
	void init();
	void update(float dt);
private:
	Transform* transform;
	float time;
};