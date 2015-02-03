#pragma once
#include "Component.h"
#include <vector>
#include <algorithm>

//class Component;

class ComponentManager {
private:
	std::vector<Component*> components;
	std::vector<Component*> destroyedComponents;
public:
	std::vector<Component*>& getComponents() const;

	ComponentManager();

	bool containsComponent(Component* component) const;
	bool removeComponent(Component* component);
	bool addComponent(Component* component);

	void update();
	void draw();

	template<class T> T* const getComponent() const {
		for (size_t i = 0; i < components.size(); i++) {
			const char* a = typeid(components[i]).name();
			const char* b = typeid(T).name();

			if (a == b) {
				return static_cast<T* const>(components[i]);
			}
		}

		return nullptr;
	}

	~ComponentManager();
};

