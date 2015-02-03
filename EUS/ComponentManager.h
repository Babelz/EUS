#pragma once
#include <vector>
#include <algorithm>

class Component;

class ComponentManager {
private:
	std::vector<Component*> components;
	std::vector<Component*> destroyedComponents;
public:
	std::vector<Component*>& const getComponents() const;

	ComponentManager();

	bool containsComponent(Component* component) const;
	bool removeComponent(Component* component);
	bool addComponent(Component* component);

	~ComponentManager();
};

