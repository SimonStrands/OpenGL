#pragma once
#include "RayTracingObject.h"

struct SphereConstantBuffer
{
	glm::vec4 positionRadious;
};

class RaySphere : public RayTracingObject
{
public:
	RaySphere(glm::vec3 position, float radius);
	SphereConstantBuffer getConstantBuffer();
private:
	float radius;
};