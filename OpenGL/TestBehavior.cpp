#include "TestBeahvior.h"

TestBehavior::TestBehavior(){
	time = 0;
}
void TestBehavior::init(){
	transform = getVariable<Transform>("Transform");
	transform->position.x += 5;
}
void TestBehavior::update(float dt){

	time += dt;
	transform->position.y = sin(time);
}