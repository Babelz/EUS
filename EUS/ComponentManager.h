#pragma once
#include "DrawableComponent.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <list>

class ComponentManager {
private:
	std::list<Component*> components;
	std::list<DrawableComponent*> drawableComponents;

	std::list<Component*> destroyedComponents;

	void freeComponents();
public:
	ComponentManager();

	bool containsComponent(Component* component) const;
	bool removeComponent(Component* component);
	bool addComponent(Component* component);

	void update();
	void draw();

	template<class T> T* const getComponent() const {
		T* foundComponent = nullptr;

		std::find_if(components.begin(), components.end(), [=, &foundComponent](Component* component) {
			foundComponent = dynamic_cast<T*>(component);

			return foundComponent != nullptr;
		});

		return foundComponent;
	}

	~ComponentManager();
};

