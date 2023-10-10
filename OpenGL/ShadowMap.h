#pragma once

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "LightBuffer.h"
#include "GameObject.h"
#include "Buffer.h"
#include "ResourceManager.h"
#include <vector>

class ShadowMap{
public:
	//Holds mutliple ShadowMaps one for each light
	ShadowMap(std::vector<Light*> lights);
	ShadowMap();
	virtual ~ShadowMap();
	void addShaderProgram(uint32_t ShadowShaderProgram);

	//Cleans the shadowMap handler and ready for new Scene
	//Just like delete
	void clean();
	
	void setLights(std::vector<Light*> lights);
	void addLight(Light* light);
	void addGameObject(GameObject* gameObject);
	void renderShadow();
	void updateLightMatrices();
	uint32_t getDepthBuffer(int index);
private:
	
	void setUpLight(Light* light, uint32_t index);
//private:
public:
	std::vector<GameObject*> gameObjectsWithShadow;
	std::vector<Light*> lights;

	std::vector<uint32_t> DepthBufferFBO;
	uint32_t DepthBufferArray;

	
	LightBuffer lightBuffer;
	uint32_t lightCB;

	ShadowMapBuffer shadowMapConstantBuffer;
	uint32_t shadowMapCB;

	uint32_t ShadowShaderProgram;
};