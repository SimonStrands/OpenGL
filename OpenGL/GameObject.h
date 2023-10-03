#pragma once
#include <glm.hpp>
#include "ComponentList.h"
#include "AnimatorModel.h"
#include "ResourceManager.h"
#include "Graphics.h"

struct DefToGameObject{
	Graphics* gfx;
	ResourceManager* rm;
};

class GameObject{
public:
	//Gonna need to add model
	GameObject(DefToGameObject& def, glm::vec3 Position = glm::vec3(), glm::vec3 Rotation = glm::vec3(), glm::vec3 Scale = glm::vec3());
	virtual ~GameObject();
	void SetShaderProgram(unsigned int shaderProgram);
	void directRender();
	void directRenderShadow();
	void addModel(Model* model);
	void setMaterial(Material mat, int index = -1);
	Material& getMaterial(int index = 0);
	void addComponent(const std::string& componentName, Components* component);
	void addBehavior(const std::string& behaviorName, Behavior* behavior, std::vector<std::pair<std::string, void*>>* variables = nullptr);
	void update(float dt);

	template <typename T>
	T* getComponent(const std::string& componentName){
		return ((T*)components[componentName]);
	}

private:
	Model* model;
	unsigned int shaderProgram;

	ResourceManager* rm;
	Graphics* gfx;

	std::map<std::string, Components*> components;
};
