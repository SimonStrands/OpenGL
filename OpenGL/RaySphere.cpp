#include "RaySphere.h"

RaySphere::RaySphere(glm::vec3 position, float radius)
{
    this->setPosition(position);
    this->radius = radius;
    this->objectType = RayObject::Sphere;
}

SphereConstantBuffer RaySphere::getConstantBuffer()
{
    return SphereConstantBuffer(glm::vec4(this->getPosition(), this->radius));
}
