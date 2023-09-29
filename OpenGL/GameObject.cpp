#include "GameObject.h"

GameObject::GameObject(ResourceManager* rm, glm::vec3 Position, glm::vec3 Rotation, glm::vec3 Scale):
	model(nullptr)
{
	shaderProgram = rm->getShaderProgram("defShaderProgram");
	components.insert(std::pair<std::string, Components*>("Transform", new Transform()));
}

GameObject::~GameObject()
{
	for (auto const& [key, val] : components)
    {
		std::cout << key << std::endl;
        delete val;
    }
}

void GameObject::SetShaderProgram(unsigned int shaderProgram)
{
	this->shaderProgram = shaderProgram;
}

void GameObject::directRender()
{
	GLTest(glUseProgram(shaderProgram));
	model->setTransform(*(Transform*)components["Transform"]);
	if(model != nullptr){
		model->DirectRender();
	}
	
}

void GameObject::directRenderShadow()
{
	model->setTransform(*(Transform*)components["Transform"]);
	if(model != nullptr){
		model->DirectRenderShadow();
	}
}

void GameObject::addModel(Model* model)
{
	this->model = model;
}

void GameObject::setMaterial(Material mat, int index)
{
	if(index < 0){
		for(int i = 0; i < model->getMeshes().size(); i++){
			model->getMeshes()[i].material = mat;
		}
	}
	else{
		model->getMeshes()[index].material = mat;
	}
}

Material& GameObject::getMaterial(int index)
{
	if (index < 0 || index > model->getMeshes().size() - 1) {
		std::cout << "cannot get that mesh index" << std::endl;
		return model->getMeshes()[0].material;
	}
	return model->getMeshes()[index].material;
}

void GameObject::addComponent(const std::string& componentName, Components* component)
{
	this->components.insert(std::pair(componentName, component));
}

void GameObject::addBehavior(const std::string& behaviorName, Behavior* behavior, std::vector<std::pair<std::string, void*>>* variables)
{
	if(components.find("BehaviorList") == components.end()){
		components.insert(std::pair("BehaviorList", new BehaviorList()));
	}
	((BehaviorList*)components.find("BehaviorList")->second)->addBehavior(behavior, behaviorName, variables);
}

void GameObject::update(float dt)
{
	if(components.find("BehaviorList") != components.end()){
		((BehaviorList*)components.find("BehaviorList")->second)->update(dt);
	}
}

Components* GameObject::getComponent(std::string componentName)
{
	return components.find(componentName)->second;
}
