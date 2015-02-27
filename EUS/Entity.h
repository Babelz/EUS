#pragma once
#include "Require.h"
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Transform.h"

class Entity {
private:
	static int idCounter; 
	
	const int id;
	
	TagContainer tags;
	ComponentManager components;
	Transform transform;

	bool visible;
	bool enabled;
	bool destroyed;

	pmath::Vec2f position;
	pmath::Vec2f size;

	std::list<Entity* const> childs;

	void freeChilds();
public:
	Entity();

	int getID() const;

	Transform& getTransform();

	void show();
	void hide();
	bool isVisible() const;

	void enable();
	void disable();
	bool isEnabled() const;
	
	void destroy();
	bool isDestroyed() const;

	bool addComponent(Component* const component);
	bool removeComponent(Component* const component);
	bool containsComponent(const Component* const component) const;

	template<class T> T* const getComponent() const {
		return components.getComponent<T>();
	}

	Component* const getComponent(std::function<bool(Component const*)> predicate) {
		return components.getComponent(predicate);
	}

	bool unTag(const std::string& tag);
	bool isTagged(const std::string& tag) const;
	bool tag(const std::string& tag);
	
	bool isParentOf(const Entity* const child);
	bool addChild(Entity* const child);
	bool removeChild(Entity* const child);

	void update(const float deltaTime);
	void draw(const float deltaTime);

	std::list<Entity* const> getChilds() const;

	~Entity();
};