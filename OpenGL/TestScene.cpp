#include "TestScene.h"
#include <iostream>


TestScene::TestScene()
{
	std::cout << "Run Test Scene" << std::endl;

}

TestScene::~TestScene()
{
	delete Plane1;
	delete Plane2;
	delete player;
	delete Sponza;
	delete Dancer;
	delete Sun;
}

void TestScene::init()
{
	gfx->vSync(false);
	basic.camera->setPosition(glm::vec3(0,5,0));
	basic.camera->setRotation(glm::vec3(0,0,0));
	Plane1 = new GameObject(defToObj);
	Plane2 = new GameObject(defToObj);
	Dancer = new GameObject(defToObj);
	Sponza = new GameObject(defToObj);
	Sun = new GameObject(defToObj);
	Sun->addModel(basic.rm->getModel("Objects/Sun.fbx"));
	Sun->getMaterial().Ka = glm::vec3(1,1,1);

	Plane1->addModel(basic.rm->getModel("Objects/Plane.fbx"));
	Plane2->addModel(basic.rm->getModel("Objects/Plane.fbx"));

	Dancer->addModel(basic.rm->getModel("Objects/sillydance2.fbx"));
	Dancer->SetShaderProgram(basic.rm->getShaderProgram("DefSkeletalAnimation"));

	Sponza->addModel(basic.rm->getModel("Objects/sponza.obj"));
	
	//basic.gfx->enableWireframeMode(true);
	
	//add the heightmap to material
	Plane1->getMaterial().HeightMap = basic.rm->getTexture("C:/Users/Simon/Desktop/UnityPrefab/Materials/ChiseledCobble/chiseled-cobble_height2.png");
	Plane1->getMaterial(0).materialFlags = MaterialFlags(Plane1->getMaterial(0).materialFlags | MaterialFlags::HeightMap);
	Plane1->SetShaderProgram(basic.rm->getShaderProgram("DefTessellation"));

	Plane2->getMaterial().HeightMap = basic.rm->getTexture("C:/Users/Simon/Desktop/UnityPrefab/Materials/ChiseledCobble/chiseled-cobble_height2.png");
	Plane2->getMaterial(0).materialFlags = MaterialFlags(Plane1->getMaterial(0).materialFlags | MaterialFlags::HeightMap);
	Plane2->SetShaderProgram(basic.rm->getShaderProgram("DefTessellation"));
	
	Plane1->getComponent<Transform>("Transform")->scale = glm::vec3(20,20,1);
	basic.shadowMap->addGameObject(Plane1);
	basic.shadowMap->addGameObject(Plane2);
	basic.shadowMap->addGameObject(Dancer);
	basic.shadowMap->addGameObject(Sponza);
	Sponza->getMaterial().d = 1;
	
	
	player = new GameObject(defToObj);
	std::vector<std::pair<std::string, void*>> playerComponents;
	playerComponents.push_back(std::pair("cam", basic.camera));
	playerComponents.push_back(std::pair("mouse", basic.mouse));
	playerComponents.push_back(std::pair("keyboard", basic.keyboard));
	playerComponents.push_back(std::pair("Transform", player->getComponent<Transform>("Transform")));
	player->addBehavior("playerUpdate", new Player(), &playerComponents);
	
	
	basic.imGuiManager->addGameObject(Plane1, "Plane1");
	basic.imGuiManager->addGameObject(Plane2, "Plane2");
	basic.imGuiManager->addGameObject(Dancer, "StormTrooper");
	basic.imGuiManager->addGameObject(Sponza, "Sponza");

	//l.push_back(new SpotLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1), 90));
	l.push_back(new DirectionalLight(glm::vec3(0,5,0), glm::vec3(0,0,0), glm::vec2(2000, 2000), glm::vec3(1,1,1)));
	//l.push_back(new PointLight(glm::vec3(0,5,0)));
	this->basic.shadowMap->setLights(l);
	basic.imGuiManager->addLight(l[0], "DirectionalLight");
	//basic.imGuiManager->addLight(l[1], "DirectionalLight");
	
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;
	//std::cout << "update()" << std::endl;

	Sun->getComponent<Transform>("Transform")->position = l[0]->position;

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

	Dancer->update(dt);
	//test->getComponent<Transform>("Transform")->rotation.x += 1 * dt;
	

	return theReturn;
}

void TestScene::render()
{
	Plane1->directRender();
	Plane2->directRender();
	Dancer->directRender();
	Sponza->directRender();
	Sun->directRender();
}
