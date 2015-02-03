#include "ComponentManager.h"

ComponentManager::ComponentManager() {
}

#pragma region Private members
void ComponentManager::freeComponents() {
	if (destroyedComponents.size() > 0) {
		std::for_each(destroyedComponents.begin(), destroyedComponents.end(), [this](Component* component) {
			components.remove(component);

			// Check if the component is drawable one.
			DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);

			if (drawableComponent != nullptr) {
				drawableComponents.remove(drawableComponent);
			}

			delete component;
			component = nullptr;
		});

		destroyedComponents.clear();
	}
}
#pragma endregion

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
		// TODO: could just check beg and end to skip sorting?
		// TODO: sorting is performed only when component gets added.
		
		// Check if component is drawable.
		DrawableComponent* drawableComponent = dynamic_cast<DrawableComponent*>(component);

		if (drawableComponent != nullptr) {
			drawableComponents.push_back(drawableComponent);

			drawableComponents.sort([](DrawableComponent* a, DrawableComponent* b) {
				return a->getDrawOrder() < b->getDrawOrder();
			});
		}

		components.push_back(component);

		components.sort([](Component* a, Component* b) {
			return a->getUpdateOrder() < b->getUpdateOrder();
		});
	}

	return add;
}

void ComponentManager::update() {
	freeComponents();
	
	std::for_each(components.begin(), components.end(), [this](Component* c) {
		// Component was destroyed in last frame, some other
		// component destroyed it or it was destroyed during 
		// draw call.
		if (c->isDestroyed()) {
			destroyedComponents.push_back(c);

			return;
		}

		c->update();
	});
}
void ComponentManager::draw() {
	std::for_each(drawableComponents.begin(), drawableComponents.end(), [this](DrawableComponent* c) {
		c->draw();
	});
}
#pragma endregion 

ComponentManager::~ComponentManager() {
	std::for_each(components.begin(), components.end(), [](Component* c) {
		delete c;
		c = nullptr;
	});
}
