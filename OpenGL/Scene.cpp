#include "Scene.h"

Scene::Scene()
{
}

void Scene::setResourceManager(ResourceManager* rm)
{
	this->rm = rm;
}

void Scene::setMouseAndKeyboard(Mouse* mouse, Keyboard* keyboard)
{
	this->mouse = mouse;
	this->keyboard = keyboard;
}

Scene::~Scene()
{
}

void Scene::init()
{
}

const int Scene::getNewSceneID()
{
	return newSceneID;
}

void Scene::switchScene(int newSceneID)
{
	this->newSceneID = newSceneID;
}

