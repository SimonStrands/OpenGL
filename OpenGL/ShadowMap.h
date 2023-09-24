#pragma once

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "LightBuffer.h"
#include "GameObject.h"
#include "BufferCreator.h"
#include "ResourceManager.h"
#include <vector>

class ShadowMap{
public:
	//Holds mutliple ShadowMaps one for each light
	ShadowMap(std::vector<Light*> lights);
	ShadowMap();
	virtual ~ShadowMap();
	void addShaderProgram(unsigned int ShadowShaderProgram);

	//Cleans the shadowMap handler and ready for new Scene
	//Just like delete
	void clean();
	
	void setLights(std::vector<Light*> lights);
	void addLight(Light* light);
	void addGameObject(GameObject* gameObject);
	void renderShadow();
private:
	void updateLightMatrices();
	void setUpLight(Light* light, unsigned int index);
private:
	std::vector<GameObject*> gameObjectsWithShadow;
	std::vector<Light*> lights;

	std::vector<unsigned int> DepthBufferFBO;
	std::vector<unsigned int> DepthBuffer;

	LightBuffer lightConstantBuffer;
	unsigned int lightCB;
	unsigned int ShadowShaderProgram;
};