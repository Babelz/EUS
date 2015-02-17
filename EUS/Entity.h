#pragma once
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Vector.hpp"
#include "Vector2.hpp"

class Entity {
private:
	static int idCounter; 
	
	const int id;
	
	TagContainer tags;
	ComponentManager components;

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

	float getWidth() const;
	float getHeight() const;
	void setWidth(const float value);
	void setHeight(const float value);

	pmath::Vec2f getSize() const;
	void setSize(const pmath::Vec2f& value);

	float getX() const;
	float getY() const;
	void setX(const float value);
	void setY(const float value);
	
	pmath::Vec2f getPosition() const;
	void setPosition(const pmath::Vec2f& value);

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

	void childsForEach(std::function<void(Entity* const)> action) const;

	void update();
	void draw();

	~Entity();
};