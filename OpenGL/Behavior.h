#pragma once
#include "Components.h"
#include <vector>
#include <map>
#include <string>

class Behavior{
public:
	Behavior();
	virtual ~Behavior() = 0; //should be pure virtual but I want it on the stack
	virtual void init();
	virtual void update(float dt);
	void addVariable(void* var, std::string variableName);
protected:
	std::map<std::string, void*> variables;
private:
	
};

class BehaviorList : public Components{
public:
	BehaviorList();
	virtual ~BehaviorList();
	void update(float dt);
	void addBehavior(Behavior* newBehavior, std::string behaviorName, std::vector<std::pair<std::string, void*>>* variables = nullptr);
	void addVariebleToBehavior(void* var, const std::string& variableName, const std::string& behaviorName, bool autoDelete = false);
private:
	std::map<std::string, Behavior*> behaviors;
	std::vector<void*> variables;
};

