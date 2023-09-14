#include "Player.h"

Player::Player()
{
}

void Player::init()
{
	cam = (Camera*)variables.find("cam")->second;
	mouse = (Mouse*)variables.find("mouse")->second;
	transform = (Transform*)variables.find("Transform")->second;
	keyboard = (Keyboard*)variables.find("keyboard")->second;
	transform->position.z = 5;
	transform->position.y = 8;
}

void Player::update(float dt)
{
	//cam->rotate(mouse->getMouseDelta());
	
	if(keyboard->getKeyDown('A')){
		moveInDirection(glm::vec3(20,0,0) * dt);
	}
	if(keyboard->getKeyDown('D')){
		moveInDirection(glm::vec3(-20,0,0) * dt);
	}
	if(keyboard->getKeyDown('W')){
		moveInDirection(glm::vec3(0,0,-20) * dt);
	}
	if(keyboard->getKeyDown('S')){
		moveInDirection(glm::vec3(0,0,20) * dt);
	}
	if(keyboard->getKeyDown(GLFW_KEY_SPACE)){
		transform->position.y += 20 * dt;
	}
	if(keyboard->getKeyDown(GLFW_KEY_LEFT_CONTROL)){
		transform->position.y -= 20 * dt;
	}
	transform->rotation.x += mouse->getMouseDelta().y * 0.01;
	transform->rotation.y -= mouse->getMouseDelta().x * 0.01; 
	transform->rotation.z = 0;
	cam->setRotation(transform->rotation);
	cam->setPosition(transform->position);
}

void Player::moveInDirection(glm::vec3 dir)
{
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -transform->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), transform->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	dir = glm::vec3(rotationMatrix * glm::vec4(dir, 1.0f));
	transform->position.x -= dir.x;
	transform->position.z -= dir.z;
}
