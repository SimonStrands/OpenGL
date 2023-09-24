#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation, float FOV):
	FOV(FOV), position(position), rotation(rotation)
{
	cb.p = glm::perspectiveFovLH(glm::radians(FOV), 16.f, 9.f, 0.1f, 2000.f);
	cb.p = glm::transpose(cb.p);
	cb.v = glm::lookAt(position, rotation, glm::vec3(0.f,1.f,0.f));
}

void Camera::init()
{
	pv = CreateUniformBuffer(cb);
	UpdateUniformBuffer(cb, pv);
	setUniform("Matrices", pv);
}

void Camera::setPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void Camera::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Camera::move(glm::vec3 direction)
{
	this->position += direction;
}

void Camera::rotate(glm::vec2 rotation)
{
	this->rotation.x += rotation.y * 0.1f;
	this->rotation.y -= rotation.x * 0.1f;
}

void Camera::moveInDirection(glm::vec3 direction)
{
	this->translation = direction;
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
                           glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	translation = glm::vec3(rotationMatrix * glm::vec4(translation, 1.0f));
	this->position.x -= translation.x;
	this->position.z -= translation.z;
}

void Camera::Update()
{
	RotationMatrix();
	cb.camPos = glm::vec4(position, 1.0f);
	UpdateUniformBuffer(cb, pv);
	setUniform("Matrices", pv, 0);
}

glm::vec3 Camera::getRotation() const
{
	return this->rotation;
}

void Camera::RotationMatrix()
{
	glm::vec3 direction;
	direction.x = cos(rotation.y) * cos(rotation.x);
	direction.y = sin(rotation.x);
	direction.z = sin(rotation.y) * cos(rotation.x);
	
	glm::vec3 cameraFront = glm::normalize(direction);
	glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0,1,0), cameraFront));
	
	cb.v = glm::lookAt(position, position + cameraFront, glm::cross(direction, cameraRight));
	cb.v = glm::transpose(cb.v);

	
}




