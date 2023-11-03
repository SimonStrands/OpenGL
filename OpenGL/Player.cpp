#include "Player.h"

Player::Player()
{
	size = sizeof(Player);
}

void Player::init()
{
	cam = getVariable<Camera>("cam");
	mouse = getVariable<Mouse>("mouse");;
	transform = getVariable<Transform>("Transform");
	keyboard = getVariable<Keyboard>("keyboard");
	transform->position.z = 5;
	transform->position.y = 8;
}

void Player::update(float dt)
{
	float speed = 20;
	if(keyboard->getKeyDown(GLFW_KEY_LEFT_SHIFT)){
		speed = 80;
	}
	if(keyboard->getKeyDown('A')){
		pressDir = 3;
		moveInDirection(dt * speed);
	}
	if(keyboard->getKeyDown('D')){
		pressDir = 2; 
		moveInDirection(dt * speed);
	}
	if(keyboard->getKeyDown('W')){
		pressDir = 0;
		moveInDirection(dt * speed);
	}
	if(keyboard->getKeyDown('S')){
		pressDir = 1;
		moveInDirection(dt * speed);
	}

	if(keyboard->getKeyDown(GLFW_KEY_SPACE)){
		transform->position.y += speed * dt;
	}
	if(keyboard->getKeyDown(GLFW_KEY_LEFT_CONTROL)){
		transform->position.y -= speed * dt;
	}
	transform->rotation.x += mouse->getMouseDelta().y * 0.01f;
	transform->rotation.y -= mouse->getMouseDelta().x * 0.01f; 
	transform->rotation.z = 0;
	cam->setRotation(transform->rotation);
	cam->setPosition(transform->position);
}

void Player::moveInDirection(float speed)
{

	glm::vec3 direction;
	direction.x = cos(transform->rotation.y) * cos(transform->rotation.x);
	direction.y = sin(transform->rotation.x);
	direction.z = sin(transform->rotation.y) * cos(transform->rotation.x);

	if(pressDir == 1){
		direction = -direction;
	}
	else if(pressDir == 2){
		direction = glm::cross(glm::vec3(0,1,0), direction);
	}
	else if(pressDir == 3){
		direction = glm::cross(direction, glm::vec3(0,1,0));
	}
	direction.y = 0;
	direction = glm::normalize(direction);
	transform->position.x -= direction.x * speed;
	transform->position.z -= direction.z * speed;
}
