#pragma once
#include <glm.hpp>
#include "ComponentList.h"
#include "Model.h"
#include "ResourceManager.h"

class GameObject{
public:
	//Gonna need to add model
	GameObject(ResourceManager* rm, glm::vec3 Position = glm::vec3(), glm::vec3 Rotation = glm::vec3(), glm::vec3 Scale = glm::vec3());
	virtual ~GameObject();
	void SetShaderProgram(unsigned int shaderProgram);
	void directRender();
	void directRenderShadow();
	void addModel(Model* model);
	void addComponent(const std::string& componentName, Components* component);
	void addBehavior(const std::string& behaviorName, Behavior* behavior, std::vector<std::pair<std::string, void*>>* variables = nullptr);
	void update(float dt);
	
	Components* getComponent(std::string componentName);

private:
	Model* model;
	unsigned int shaderProgram;

	std::map<std::string, Components*> components;
};
