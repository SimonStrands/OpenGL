#include "ShadowMap.h"

ShadowMap::ShadowMap(std::vector<Light*> lights)
{
	setLights(lights);
	lightCB = CreateUniformBuffer(lightConstantBuffer);
}

ShadowMap::ShadowMap()
{
	lightCB = CreateUniformBuffer(lightConstantBuffer);
}

void ShadowMap::clean()
{
	//Handle deletion of lights
	for(int i = 0; i < lights.size(); i++){
		delete lights[i];
	}
	//Does not handle deleteion of gameObject where they can be static/on the stack
	while(gameObjectsWithShadow.size() > 0){
		gameObjectsWithShadow.pop_back();
	}
	for(int i = 0; i < DepthBufferFBO.size(); i++){
		glDeleteBuffers(1, &DepthBufferFBO[i]);
		glDeleteBuffers(1, &DepthBuffer[i]);
	}
	
}

void ShadowMap::setLights(std::vector<Light*> lights)
{
	if(this->lights.size() > 0){
		clean();
	}
	this->lights = lights;

	if(this->lights.size() > MAXNUMBEROFLIGHTS){
		std::cout << "Error: number of lights exceded the max number!" << std::endl;
		while(this->lights.size() > MAXNUMBEROFLIGHTS){
			this->lights.pop_back();
		}
	}

	DepthBufferFBO.resize(this->lights.size());
	DepthBuffer.resize(this->lights.size());
	lightConstantBuffer.nrOfLight = (int)this->lights.size();


	for(int i = 0; i < this->lights.size(); i++)
	{
		if (this->lights[i]->lightType != LightType::e_PointLight)
		{
			setUpLight(this->lights[i], i);
		}
	}
}

void ShadowMap::addGameObject(GameObject* gameObject)
{
	gameObjectsWithShadow.push_back(gameObject);
}

void ShadowMap::renderShadow()
{
	glUseProgram(ShadowShaderProgram);

	for(int i = 0; i < lights.size(); i++){
		
		if(lights[i]->lightType ==  LightType::e_DirectionlLight){
			DirectionalLight* dl = (DirectionalLight*)lights[i];

			glViewport(0, 0, dl->WidthHeight.x, dl->WidthHeight.y);
			glBindFramebuffer(GL_FRAMEBUFFER, DepthBufferFBO[i]);
			glClear(GL_DEPTH_BUFFER_BIT);

			for(int i = 0; i < gameObjectsWithShadow.size(); i++){
				gameObjectsWithShadow[i]->directRenderShadow();
			}
		}
		if(lights[i]->lightType ==  LightType::e_SpotLight){
			SpotLight* dl = (SpotLight*)lights[i];

			glViewport(0, 0, dl->WidthHeight.x, dl->WidthHeight.y);
			glBindFramebuffer(GL_FRAMEBUFFER, DepthBufferFBO[i]);
			glClear(GL_DEPTH_BUFFER_BIT);

			for(int i = 0; i < gameObjectsWithShadow.size(); i++){
				gameObjectsWithShadow[i]->directRenderShadow();
			}
		}
	}
}

ShadowMap::~ShadowMap()
{
	clean();
	//delete lightCB
}

void ShadowMap::addShaderProgram(unsigned int ShadowShaderProgram)
{
	this->ShadowShaderProgram = ShadowShaderProgram;
}

void ShadowMap::updateLightMatrices()
{
	for(int i = 0; i < lights.size(); i++){
		lightConstantBuffer.lightPos[i] = glm::vec4(lights[i]->position, lights[i]->lightType);
		lightConstantBuffer.lightColors[i] = glm::vec4(lights[i]->color, 0);
		lightConstantBuffer.lightViewProjection[i] = lights[i]->getLightViewProj();
	}
	UpdateUniformBuffer(lightConstantBuffer, lightCB);
	setUniform("LightData", lightCB, 5);
}

void ShadowMap::setUpLight(Light* light, unsigned int index)
{
	if(light->lightType == LightType::e_DirectionlLight)
	{
		DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);
		createDepthStencil(dirLight->WidthHeight.x, dirLight->WidthHeight.y, DepthBufferFBO[index], DepthBuffer[index]);
	}
	else if(light->lightType == LightType::e_SpotLight)
	{
		SpotLight* dirLight = dynamic_cast<SpotLight*>(light);
		createDepthStencil(dirLight->WidthHeight.x, dirLight->WidthHeight.y, DepthBufferFBO[index], DepthBuffer[index]);
	}
}
