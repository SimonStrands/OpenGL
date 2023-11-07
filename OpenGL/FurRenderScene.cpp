#include "FurRenderScene.h"

FurRenderScene::FurRenderScene()
{
	std::cout << "Run Test Scene" << std::endl;
}

FurRenderScene::~FurRenderScene()
{
}

void FurRenderScene::init()
{
	rm->createShaderProgram("test", rm->getShader("FurShaderVertex.vert"), rm->getShader("FurShaderPixel.frag"), rm->getShader("FurShaderGeometry.geom"));


	gfx->vSync(false);
	basic.camera->setPosition(glm::vec3(0,5,0));
	
	FurPlane = new GameObject(defToObj);
	FurPlane->addModel(rm->getModel("Plane.fbx"));
	FurPlane->getComponent<Transform>("Transform")->rotation.y = 1.57;
	FurPlane->SetShaderProgram(rm->getShaderProgram("test"));

	plane2 = gh->createGameObject();
	plane2->addModel(rm->getModel("Plane.fbx"));
	plane2->getComponent<Transform>("Transform")->rotation.y = 1.57;
	plane2->getComponent<Transform>("Transform")->scale.y = 10;
	plane2->getComponent<Transform>("Transform")->scale.x = 10;
	plane2->getComponent<Transform>("Transform")->position.y = -1;
	
	player = gh->createGameObject();
	std::vector<std::pair<std::string, TLVarieble>> playerComponents;
	playerComponents.push_back(std::pair("cam", TLVarieble(basic.camera)));
	playerComponents.push_back(std::pair("mouse", TLVarieble(basic.mouse)));
	playerComponents.push_back(std::pair("keyboard", TLVarieble(basic.keyboard)));
	playerComponents.push_back(std::pair("Transform", TLVarieble(player->getComponent<Transform>("Transform"))));
	player->addBehavior("playerUpdate", new Player(), &playerComponents);
	
	l.push_back(new PointLight(glm::vec3(0,20,0)));
	basic.shadowMap->setLights(l);
	basic.imGuiManager->addLight(l[0], "PointLight");
	basic.imGuiManager->addGameObject(FurPlane, "FurPlane");
	basic.imGuiManager->addGameObject(plane2, "Plane2");
}

SceneHandlerCalls FurRenderScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;


	return theReturn;
}

void FurRenderScene::render()
{
	FurPlane->directRender();
}
