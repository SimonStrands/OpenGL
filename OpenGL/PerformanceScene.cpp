#include "PerformanceScene.h"

PerformanceScene::PerformanceScene()
{
}

PerformanceScene::~PerformanceScene()
{
}

void PerformanceScene::init()
{
    gfx->vSync(false);
    gh->createGameObject("Sponza");
    gh->getGameObject("Sponza")->addModel(rm->getModel("sponza.obj.OEM"));

    gh->createGameObject("player");
	std::vector<std::pair<std::string, TLVarieble>> playerComponents;
	playerComponents.push_back(std::pair("cam", TLVarieble(basic.camera)));
	playerComponents.push_back(std::pair("mouse", TLVarieble(basic.mouse)));
	playerComponents.push_back(std::pair("keyboard", TLVarieble(basic.keyboard)));
	playerComponents.push_back(std::pair("Transform", TLVarieble(gh->getGameObject("player")->getComponent<Transform>("Transform"))));
	gh->getGameObject("player")->addBehavior("playerUpdate", new Player(), &playerComponents);

    std::vector<Light*> lights;
    lights.push_back(new SpotLight(
        glm::vec3(0, 500, 0), 
        glm::vec3(0,0,0), 
        glm::vec2(2000,2000), glm::vec3(100,100,150)
    ));
    this->basic.shadowMap->setLights(lights);
    basic.imGuiManager->addLight(lights[0], "PointLight");
}

SceneHandlerCalls PerformanceScene::update(float dt)
{
    return SceneHandlerCalls::NOTHING;
}

void PerformanceScene::render()
{
}
