#include "ShadowMap.h"

ShadowMap::ShadowMap(std::vector<Light*> lights)
{
	setLights(lights);
	shadowMapCB = CreateUniformBuffer(shadowMapConstantBuffer);
	lightCB = CreateUniformBuffer(lightBuffer);
}

ShadowMap::ShadowMap()
{
	shadowMapCB = CreateUniformBuffer(shadowMapConstantBuffer);
	lightCB = CreateUniformBuffer(lightBuffer);
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
		glDeleteBuffers(1, &DepthBufferArray);
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
	shadowMapConstantBuffer.nrOfLight = (int)this->lights.size();
	lightBuffer.projection = this->lights[0]->getProjection();
	lightBuffer.view = glm::mat4(1);

	float MaxWidth = 0, MaxHeight = 0;
	for(int i = 0; i < this->lights.size(); i++){
		if (this->lights[i]->lightType == LightType::e_SpotLight)
		{
			SpotLight* sl = (SpotLight*)lights[i];
			if(MaxWidth < sl->WidthHeight.x){
				MaxWidth = sl->WidthHeight.x;
			}
			if(MaxHeight < sl->WidthHeight.y){
				MaxHeight = sl->WidthHeight.y;
			}
		}
		else if(this->lights[i]->lightType == LightType::e_DirectionlLight)
		{
			DirectionalLight* dl = (DirectionalLight*)lights[i];
			if(MaxWidth < dl->WidthHeight.x){
				MaxWidth = dl->WidthHeight.x;
			}
			if(MaxHeight < dl->WidthHeight.y){
				MaxHeight = dl->WidthHeight.y;
			}
		}
	}

	glGenTextures(1, &DepthBufferArray);
	glBindTexture(GL_TEXTURE_2D_ARRAY, DepthBufferArray);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_DEPTH_COMPONENT32F, MaxWidth, MaxHeight, this->lights.size());

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	static const float clampColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, clampColor);
	
	for (size_t i = 0; i < this->lights.size(); ++i) {
	    glGenFramebuffers(1, &DepthBufferFBO[i]);
	    glBindFramebuffer(GL_FRAMEBUFFER, DepthBufferFBO[i]);
	    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthBufferArray, 0, i);
	    glDrawBuffer(GL_NONE);
	    glReadBuffer(GL_NONE);
	    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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

			lightBuffer.projection = dl->getProjection();
			lightBuffer.view = dl->getLightView();
			UpdateUniformBuffer(lightBuffer, lightCB);
			setUniform("LightData", lightCB, 5);

			glViewport(0, 0, dl->WidthHeight.x, dl->WidthHeight.y);
			glBindFramebuffer(GL_FRAMEBUFFER, DepthBufferFBO[i]);
			glClear(GL_DEPTH_BUFFER_BIT);

			for(int i = 0; i < gameObjectsWithShadow.size(); i++){
				gameObjectsWithShadow[i]->directRenderShadow();
			}
		}
		if(lights[i]->lightType ==  LightType::e_SpotLight){
			SpotLight* sl = (SpotLight*)lights[i];

			lightBuffer.projection = sl->getProjection();
			lightBuffer.view = sl->getLightView();
			UpdateUniformBuffer(lightBuffer, lightCB);
			setUniform("LightData", lightCB, 5);

			glViewport(0, 0, sl->WidthHeight.x, sl->WidthHeight.y);
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
	//delete shadowMapCB
}

void ShadowMap::addShaderProgram(unsigned int ShadowShaderProgram)
{
	this->ShadowShaderProgram = ShadowShaderProgram;
}

void ShadowMap::updateLightMatrices()
{
	glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthBufferArray);
	for(int i = 0; i < lights.size(); i++){
		shadowMapConstantBuffer.lightPos[i] = glm::vec4(lights[i]->position, lights[i]->lightType);
		shadowMapConstantBuffer.lightColors[i] = glm::vec4(lights[i]->color, 0);
		shadowMapConstantBuffer.lightViewProjection[i] = lights[i]->getLightViewProj();
	}
	UpdateUniformBuffer(shadowMapConstantBuffer, shadowMapCB);
	setUniform("ShadowData", shadowMapCB, 3);
}

unsigned int ShadowMap::getDepthBuffer(int index)
{
	return DepthBufferFBO[index];
}


//void ShadowMap::setUpLight(Light* light, unsigned int index)
//{
//	if(light->lightType == LightType::e_DirectionlLight)
//	{
//		DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(light);
//		createDepthStencil(dirLight->WidthHeight.x, dirLight->WidthHeight.y, DepthBufferFBO[index], DepthBuffer[index]);
//	}
//	else if(light->lightType == LightType::e_SpotLight)
//	{
//		SpotLight* dirLight = dynamic_cast<SpotLight*>(light);
//		createDepthStencil(dirLight->WidthHeight.x, dirLight->WidthHeight.y, DepthBufferFBO[index], DepthBuffer[index]);
//	}
//}
