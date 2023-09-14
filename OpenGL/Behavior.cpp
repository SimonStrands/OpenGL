#include "Behavior.h"

Behavior::Behavior()
{
}

Behavior::~Behavior()
{
}

void Behavior::init()
{
}

void Behavior::update(float dt)
{
}

void Behavior::addVariable(void* var, std::string variableName)
{
    variables.insert(std::pair(variableName, var));
}

BehaviorList::BehaviorList()
{
}

BehaviorList::~BehaviorList()
{
    for(int i = 0; i < variables.size(); i++){
        delete variables[i];
    }
    for (auto & x : behaviors)
    {
        delete x.second;
    }
}

void BehaviorList::update(float dt)
{
	for (auto & x : behaviors)
    {
        x.second->update(dt);
    }
}

void BehaviorList::addBehavior(Behavior* newBehavior, std::string behaviorName, std::vector<std::pair<std::string, void*>>* variables)
{
    behaviors.insert(std::pair(behaviorName, newBehavior));
    if(variables != nullptr){
        for(int i = 0; i < variables->size(); i++){
            newBehavior->addVariable(variables->at(i).second, variables->at(i).first);
        }
    }
    newBehavior->init();
}

void BehaviorList::addVariebleToBehavior(void* var, const std::string& variableName, const std::string& behaviorName, bool autoDelete)
{
    behaviors.find(behaviorName)->second->addVariable(var, variableName);
    if(autoDelete){
        variables.push_back(var);
    }
}
