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
	//test->addModel(basic.rm->getModel("Objects/Human_806polys.fbx"));
	//Sponza->addModel(basic.rm->getModel("Objects/sponza.obj"));

	test->addModel(basic.rm->getModel("Objects/Cube.fbx"));
	box2->addModel(basic.rm->getModel("Objects/sillydance2.fbx"));
	box2->SetShaderProgram(basic.rm->getShaderProgram("DefSkeletalAnimation"));
	Sponza->addModel(basic.rm->getModel("Objects/Plane.fbx"));
	
	//basic.gfx->enableWireframeMode(true);
	
	//add the heightmap to material
	Sponza->getMaterial().HeightMap = basic.rm->getTexture("C:/Users/Simon/Desktop/UnityPrefab/Materials/ChiseledCobble/chiseled-cobble_height2.png");
	Sponza->getMaterial(0).materialFlags = MaterialFlags(Sponza->getMaterial(0).materialFlags | MaterialFlags::HeightMap);
	Sponza->SetShaderProgram(basic.rm->getShaderProgram("DefTessellation"));
	
	
	basic.shadowMap->addGameObject(test);
	basic.shadowMap->addGameObject(box2);
	basic.shadowMap->addGameObject(Sponza);
	Sponza->getMaterial().d = 1;
	
	Sponza->getComponent<Transform>("Transform")->scale = glm::vec3(20,20,0.5);
	
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
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;
	//std::cout << "update()" << std::endl;

	basic.camera->Update();

	if(basic.keyboard->getKeyDown('N')){
		Sponza->getMaterial().d = 1;
	}
	else{
		Sponza->getMaterial().d = 0;
	}
	box2->update(dt);
	test->getComponent<Transform>("Transform")->rotation.x += 1 * dt;
	player->update(dt);

	return theReturn;
}

void TestScene::render()
{
	//test->directRender();
	box2->directRender();
	//Sponza->directRender();
}
