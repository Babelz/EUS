#pragma once
#include "Require.h"
#include "TagContainer.h"
#include "ComponentManager.h"
#include "Component.h"
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Transform.h"

__declspec(align(16))
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

	std::list<Entity* const> childs;

	void freeChilds();
public:
	Entity();

	int getID() const;

	Transform& getTransform();

	void show();
	void hide();
	const bool isVisible() const;

	void enable();
	void disable();
	const bool isEnabled() const;
	
	void destroy();
	const bool isDestroyed() const;

	const bool addComponent(Component* const component);
	const bool removeComponent(Component* const component);
	const bool containsComponent(const Component* const component) const;

	template<class T> T* const getComponent() const {
		return components.getComponent<T>();
	}

	Component* const getComponent(std::function<bool(Component const*)> predicate) {
		return components.getComponent(predicate);
	}

	const bool unTag(const std::string& tag);
	const bool isTagged(const std::string& tag) const;
	const bool tag(const std::string& tag);
	
	const bool isParentOf(const Entity* const child);
	const bool addChild(Entity* const child);
	const bool removeChild(Entity* const child);

	const size_t childsCount() const;
	Entity* childAtIndex(const size_t index);

	void update(const float deltaTime);
	void draw(const float deltaTime);

	std::list<Entity* const> getChilds() const;

	~Entity();

	void* operator new (const size_t i){
		return _mm_malloc(i, 16);
	}

	void operator delete(void* chunk) {
		_mm_free(chunk);
	}
};