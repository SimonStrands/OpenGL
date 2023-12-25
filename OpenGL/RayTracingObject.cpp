#include "RayTracingObject.h"

RayTracingObject::RayTracingObject()
{
}

RayTracingObject::~RayTracingObject()
{
}

RayObject RayTracingObject::getObjectType() const
{
    return objectType;
}

glm::vec3 RayTracingObject::getPosition()
{
    return this->position;
}

void RayTracingObject::setPosition(const glm::vec3& position)
{
    this->position = position;
}
