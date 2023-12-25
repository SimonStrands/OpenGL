#pragma once
#include "glm.hpp"

enum RayObject {
	Sphere = 1,
	AABB = 2,
	OBB = 3,
	Traingles = 4
};

class RayTracingObject
{
public:
	RayTracingObject();
	virtual ~RayTracingObject();
	RayObject getObjectType() const;

	glm::vec3 getPosition();
	void setPosition(const glm::vec3& position);
protected:
	RayObject objectType;
private:
	glm::vec3 position;
	
};