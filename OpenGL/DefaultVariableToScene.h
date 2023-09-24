#pragma once
#include "Camera.h"
#include "ShadowMap.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ResourceManager.h"

struct DefaultVariableToScene{
	Camera* camera;
	ResourceManager* rm;
	Mouse* mouse;
	Keyboard* keyboard;
	ShadowMap* shadowMap;
};