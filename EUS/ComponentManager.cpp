#include "ComponentManager.h"

ComponentManager::ComponentManager() {
}

#pragma region Public members
bool ComponentManager::containsComponent(Component* component) const {
	return std::find(components.begin(), components.end(), component) != components.end();
}
bool ComponentManager::removeComponent(Component* component) {
	bool remove = containsComponent(component);

	if (remove) {
		components.erase(std::remove(components.begin(), components.end(), component), components.end());
	}

	return remove;
}
bool ComponentManager::addComponent(Component* component) {
	bool add = !containsComponent(component);

	if (add) {
		components.push_back(component);

		// TODO: sort components based on their draw and update orders.
	}

	return add;
}

void ComponentManager::update() {
	std::for_each(components.begin(), components.end(), [](Component* c) {
		c->update();
	});
}
void ComponentManager::draw() {
	// TODO: draw components.
}
#pragma endregion 

ComponentManager::~ComponentManager() {
	for (size_t i = 0; i < components.size(); i++) {
		delete components[i];

		components[i] = 0;
	}
}
