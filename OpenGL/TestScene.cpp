#include "TestScene.h"
#include <iostream>

#include <chrono>


TestScene::TestScene()
{
	std::cout << "Run Test Scene" << std::endl;

}

TestScene::~TestScene()
{
}

void TestScene::init()
{
	dq = new DrawQuad(rm, basic.shaderHandler);
	gfx->vSync(false);
	basic.camera->setPosition(glm::vec3(0,5,0));
	basic.camera->setRotation(glm::vec3(0,0,0));

	Sun = gh->createGameObject("", false);
	
	Sun->addModel(basic.rm->getModel("sun.fbx"));
	Sun->getMaterial().Ka = glm::vec3(1,1,1);
	
	
	player = gh->createGameObject();
	std::vector<std::pair<std::string, TLVarieble>> playerComponents;
	playerComponents.push_back(std::pair("cam", TLVarieble(basic.camera)));
	playerComponents.push_back(std::pair("mouse", TLVarieble(basic.mouse)));
	playerComponents.push_back(std::pair("keyboard", TLVarieble(basic.keyboard)));
	playerComponents.push_back(std::pair("Transform", TLVarieble(player->getComponent<Transform>("Transform"))));
	player->addBehavior("playerUpdate", new Player(), &playerComponents);

	//l.push_back(new SpotLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1), 90));
	l.push_back(new DirectionalLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(500, 500), glm::vec3(1,1,1), glm::vec2(2,2),0));
	l.push_back(new PointLight(glm::vec3(0,5,0)));
	this->basic.shadowMap->setLights(l);
	basic.imGuiManager->addLight(l[0], "DirectionalLight");
	basic.imGuiManager->addLight(l[1], "PointLight");
	//basic.imGuiManager->addLight(l[1], "DirectionalLight");
	
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;

	Sun->getComponent<Transform>("Transform")->position = l[0]->position;

	basic.camera->Update();

	if(basic.keyboard->getKeyDown('N')){
		this->MainCamera->setProjection(l[0]->getProjection());
		this->MainCamera->getPosition() = l[0]->position;
		DirectionalLight* dl = dynamic_cast<DirectionalLight*>(l[0]);
		this->MainCamera->setRotation(dl->rotation);
	}
	else{
		this->MainCamera->setProjection(glm::transpose(glm::perspectiveFovLH(glm::radians(45.f), 16.f, 9.f, 0.1f, 2000.f)));
	}
	

	return theReturn;
}

void TestScene::render()
{
	dq->render();
}
