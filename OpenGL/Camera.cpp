#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 rotation, float FOV):
	FOV(FOV), position(position), rotation(rotation)
{
	cb.p = glm::perspectiveFovLH(glm::radians(FOV), 16.f, 9.f, 0.01f, 2000.f);
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
	this->rotation.x += rotation.y * 0.01f;
	this->rotation.y -= rotation.x * 0.01f;
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
	UpdateUniformBuffer(cb, pv);
	setUniform("Matrices", pv);
}

void Camera::RotationMatrix()
{
	glm::quat camOrientation;
	camOrientation = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));
	cb.v = glm::mat4_cast(camOrientation);
	cb.v = glm::translate(cb.v, -position);
	cb.v = glm::transpose(cb.v);
}





