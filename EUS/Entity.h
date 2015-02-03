#pragma once
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"

class Entity {
private:
	TagContainer tags;
	ComponentManager components;

	bool visible;
	bool enabled;
	bool destroyed;
public:
	Entity();

	void show();
	void hide();
	bool isVisible() const;

	void enable();
	void disable();
	bool isEnabled() const;
	
	void destroy();
	bool isDestroyed() const;

	bool addComponent(Component* component);
	bool removeComponent(Component* component);
	bool containsComponent(Component* const component) const;

	template<class T> T* const getComponent() const {
		return components.getComponent<T>();
	}

	bool unTag(std::string tag);
	bool isTagged(std::string tag) const;
	bool tag(std::string tag);

	void update();
	void draw();

	~Entity();
};