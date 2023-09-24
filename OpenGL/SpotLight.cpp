#include "SpotLight.h"

glm::mat4 SpotLight::getLightViewProj()
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
