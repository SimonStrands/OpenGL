#pragma once

#include <glm.hpp>
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/quaternion.hpp"
#include "BufferCreator.h"

class Camera{
public:
	Camera(glm::vec3 position = glm::vec3(), glm::vec3 rotation = glm::vec3(), float FOV = 45);
	void init();
	void setPosition(glm::vec3 newPosition);
	void setRotation(glm::vec3 rotation);
	void move(glm::vec3 direction);
	void rotate(glm::vec2 rotation);//skipping Z
	void moveInDirection(glm::vec3 direction = glm::vec3(0,0,1));
	void Update();

private:
	void RotationMatrix();
	glm::vec3 translation;
	struct cameraBuffer{
		glm::mat4 p;
		glm::mat4 v;
	};
	cameraBuffer cb;
	unsigned int pv;
	glm::vec3 position;
	glm::vec3 rotation;
	float FOV;
};
