#pragma once
#include <glm.hpp>
#define MAXNUMBEROFLIGHTS 6
struct LightBuffer{
	glm::vec4 lightPos[MAXNUMBEROFLIGHTS];//4:th element is what type of light it is
	glm::vec4 lightColors[MAXNUMBEROFLIGHTS];//4:th element is how hard the shadows should be
	glm::mat4 lightViewProjection[MAXNUMBEROFLIGHTS];
	int nrOfLight;
};