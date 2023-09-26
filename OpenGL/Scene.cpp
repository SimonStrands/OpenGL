#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::init()
{
}

void Scene::setBasicVariables(DefaultVariableToScene& basic)
{
	this->basic.camera = basic.camera;
	this->basic.keyboard = basic.keyboard;
	this->basic.mouse = basic.mouse;
	this->basic.rm = basic.rm;
	this->basic.shadowMap = basic.shadowMap;
	this->basic.imGuiManager = basic.imGuiManager;
}

const int Scene::getNewSceneID()
{
	return newSceneID;
}

void Scene::switchScene(int newSceneID)
{
	this->newSceneID = newSceneID;
}

