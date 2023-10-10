#include "TestScene.h"
#include <iostream>


TestScene::TestScene()
{
	std::cout << "Run Test Scene" << std::endl;

}

TestScene::~TestScene()
{
	delete test;
	delete player;
	delete Sponza;
	delete box2;
}

void TestScene::init()
{
	basic.camera->setPosition(glm::vec3(0,5,0));
	basic.camera->setRotation(glm::vec3(0,0,0));
	test = new GameObject(defToObj);
	Sponza = new GameObject(defToObj);
	box2 = new GameObject(defToObj);

	test->addModel(basic.rm->getModel("Objects/Plane.fbx"));
	box2->addModel(basic.rm->getModel("Objects/sillydance2.fbx"));
	box2->SetShaderProgram(basic.rm->getShaderProgram("DefSkeletalAnimation"));
	Sponza->addModel(basic.rm->getModel("Objects/sponza.obj"));
	
	//basic.gfx->enableWireframeMode(true);
	
	//add the heightmap to material
	test->getMaterial().HeightMap = basic.rm->getTexture("C:/Users/Simon/Desktop/UnityPrefab/Materials/ChiseledCobble/chiseled-cobble_height2.png");
	test->getMaterial(0).materialFlags = MaterialFlags(test->getMaterial(0).materialFlags | MaterialFlags::HeightMap);
	test->SetShaderProgram(basic.rm->getShaderProgram("DefTessellation"));
	
	test->getComponent<Transform>("Transform")->scale = glm::vec3(20,20,1);
	basic.shadowMap->addGameObject(test);
	basic.shadowMap->addGameObject(box2);
	basic.shadowMap->addGameObject(Sponza);
	Sponza->getMaterial().d = 1;
	
	
	player = new GameObject(defToObj);
	std::vector<std::pair<std::string, void*>> playerComponents;
	playerComponents.push_back(std::pair("cam", basic.camera));
	playerComponents.push_back(std::pair("mouse", basic.mouse));
	playerComponents.push_back(std::pair("keyboard", basic.keyboard));
	playerComponents.push_back(std::pair("Transform", player->getComponent<Transform>("Transform")));
	player->addBehavior("playerUpdate", new Player(), &playerComponents);
	
	
	basic.imGuiManager->addGameObject(test, "Cube");
	basic.imGuiManager->addGameObject(box2, "Cube2");
	basic.imGuiManager->addGameObject(Sponza, "Plane");
	basic.imGuiManager->addGameObject(player, "player");

	//l.push_back(new SpotLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1), 90));
	l.push_back(new DirectionalLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1)));
	this->basic.shadowMap->setLights(l);
	basic.imGuiManager->addLight(l[0], "Spotlight");
	//basic.imGuiManager->addLight(l[1], "DirectionalLight");
	
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;
	//std::cout << "update()" << std::endl;

	basic.camera->Update();
	player->update(dt);

	if(basic.keyboard->getKeyDown('N')){
		this->MainCamera->setProjection(l[0]->getProjection());
		this->MainCamera->getPosition() = l[0]->position;
		DirectionalLight* dl = dynamic_cast<DirectionalLight*>(l[0]);
		this->MainCamera->setRotation(dl->rotation);
	}
	else{
		this->MainCamera->setProjection(glm::transpose(glm::perspectiveFovLH(glm::radians(45.f), 16.f, 9.f, 0.1f, 2000.f)));
	}

	box2->update(dt);
	//test->getComponent<Transform>("Transform")->rotation.x += 1 * dt;
	

	return theReturn;
}

void TestScene::render()
{
	test->directRender();
	box2->directRender();
	Sponza->directRender();
}
