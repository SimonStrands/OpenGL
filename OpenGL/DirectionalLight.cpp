#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 position, glm::vec3 rotation, glm::vec2 WH, glm::vec3 color, glm::vec2 scale):
	rotation(rotation),
	WidthHeight(WH)
{
	this->position = position;
	this->color = color;
	this->lightType = LightType::e_DirectionlLight;
	projectonMatrix = glm::transpose(glm::orthoLH(-WH.x/2.f, WH.x/2.f, -WH.y/2.f, WH.y/2.f, 0.1f, 2000.f));
}

glm::mat4 DirectionalLight::getLightViewProj()
{
	glm::mat4 theReturn = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-position.x, -position.y, -position.z, 1.0f
	);
	//xRotation
	theReturn = theReturn * glm::mat4(
		 std::cos(rotation.x), 0.0f, std::sin(rotation.x), 0.0f ,
		 0.0f,			 1.0f,	0.0f,			 0.0f ,
		 -std::sin(rotation.x),0.0f, std::cos(rotation.x), 0.0f ,
		 0.0f,			 0.0f,			 0.0f,  1.0f 
	);
	//yRotation
	theReturn = theReturn * glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cos(rotation.y), std::sin(rotation.y), 0.0f,
		0.0f, -std::sin(rotation.y), std::cos(rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	//z rotation
	theReturn = theReturn * glm::mat4(
		std::cos(rotation.z), -std::sin(rotation.z), 0.0f, 0.0f,
		std::sin(rotation.z), std::cos(rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	//Should the return be -?
    return theReturn * projectonMatrix;
}

glm::mat4 DirectionalLight::getLightView()
{
	glm::mat4 theReturn = glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-position.x, -position.y, -position.z, 1.0f
	);
	//xRotation
	theReturn = theReturn * glm::mat4(
		 std::cos(rotation.x), 0.0f, std::sin(rotation.x), 0.0f ,
		 0.0f,			 1.0f,	0.0f,			 0.0f ,
		 -std::sin(rotation.x),0.0f, std::cos(rotation.x), 0.0f ,
		 0.0f,			 0.0f,			 0.0f,  1.0f 
	);
	//yRotation
	theReturn = theReturn * glm::mat4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, std::cos(rotation.y), std::sin(rotation.y), 0.0f,
		0.0f, -std::sin(rotation.y), std::cos(rotation.y), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	//z rotation
	theReturn = theReturn * glm::mat4(
		std::cos(rotation.z), -std::sin(rotation.z), 0.0f, 0.0f,
		std::sin(rotation.z), std::cos(rotation.z), 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	return theReturn;
}
