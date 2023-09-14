#include "TestScene.h"
#include <iostream>


TestScene::TestScene():
	cam(glm::vec3(0,0,5),glm::vec3(0,0,0))
{
	std::cout << "Run Test Scene" << std::endl;
}

TestScene::~TestScene()
{
	delete test;
	delete player;
	delete Sponza;
}

void TestScene::init()
{
	test = new GameObject(rm);
	Sponza = new GameObject(rm);
	test->addModel(rm->getModel("Objects/Human_806polys.fbx"));
	Sponza->addModel(rm->getModel("Objects/Camera.obj"));
	cam.init();
	//
	player = new GameObject(rm);
	std::vector<std::pair<std::string, void*>> playerComponents;
	playerComponents.push_back(std::pair("cam", &cam));
	playerComponents.push_back(std::pair("mouse", mouse));
	playerComponents.push_back(std::pair("keyboard", keyboard));
	playerComponents.push_back(std::pair("Transform", player->getComponent("Transform")));
	player->addBehavior("playerUpdate", new Player(), &playerComponents);
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;
	//std::cout << "update()" << std::endl;

	cam.Update();
	((Transform*)test->getComponent("Transform"))->rotation.y += 0.01;
	player->update(dt);
	return theReturn;
}

void TestScene::render()
{
	test->directRender();
	Sponza->directRender();
}
