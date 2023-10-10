#pragma once
#include "Graphics.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

class ImGuiManager{
public:
	ImGuiManager();
	void init();
	void render();

	void addGameObject(GameObject* gameObject, std::string name = "");
	void addLight(Light* light, std::string name = "");
	void setTexture(unsigned int buffer, glm::vec2 size);
private:
	unsigned int Image;
	glm::vec2 textureWidthHeight;

	void renderGameObject();//and Lights
	void renderTexture();
private:
	std::vector<std::pair<GameObject*, std::string>> gameObjects;
	std::vector<std::pair<Light*, std::string>> lights;
};