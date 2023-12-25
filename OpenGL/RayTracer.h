#pragma once
#include "RaySphere.h"
#include "DrawQuad.h"
#include <vector>

class RayTracer
{
public:
#define ScreenWidth 800
#define ScreenHeight 800
	RayTracer(ResourceManager* rm, ShaderHandler* sh);
	void addObject(RayTracingObject* object);
	void render();
private:
	ResourceManager* rm;
	ShaderHandler* sh;
	DrawQuad qd;
	std::vector<RayTracingObject*> objects;
};