#pragma once
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Vector.hpp"
#include "Vector2.hpp"

class Entity {
private:
	TagContainer tags;
	ComponentManager components;

	bool visible;
	bool enabled;
	bool destroyed;

	pmath::Vec2f position;
	pmath::Vec2f size;
public:
	Entity();

	float getWidth() const;
	float getHeight() const;
	void setWidth(float value);
	void setHeight(float value);

	pmath::Vec2f getSize() const;
	void setSize(pmath::Vec2f value);

	float getX() const;
	float getY() const;
	void setX(float value);
	void setY(float value);
	
	pmath::Vec2f getPosition() const;
	void setPosition(pmath::Vec2f value);

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
	bool containsComponent(Component* const component) const;

	template<class T> T* const getComponent() const {
		return components.getComponent<T>();
	}

	bool unTag(const std::string& tag);
	bool isTagged(const std::string& tag) const;
	bool tag(const std::string& tag);

	void update();
	void draw();

	~Entity();
};