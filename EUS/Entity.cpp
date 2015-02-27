#include "Entity.h"

int Entity::idCounter = 0;

Entity::Entity() : id(idCounter++), 
				   visible(true),
				   enabled(true),
				   destroyed(false) {
}

#pragma region Public members
int Entity::getID() const {
	return id;
}

Transform& Entity::getTransform() {
	return transform;
}

void Entity::show() {
	visible = true;
}
void Entity::hide() {
	visible = false;
}
bool Entity::isVisible() const {
	return visible;
}

void Entity::enable() {
	enabled = true;
}
void Entity::disable() {
	enabled = false;
}
bool Entity::isEnabled() const {
	return enabled;
}

void Entity::destroy() {
	if (destroyed) {
		return;
	}

	components.freeComponents();

	for_each(childs.begin(), childs.end(), [](Entity* c) {
		c->destroy();
	});

	childs.clear();

	destroyed = true;
}
bool Entity::isDestroyed() const {
	return destroyed;
}

// All wrapper methods return false if the entity is in destroyed state and 
// wont complete the wanted operation (adding/removing tags).

// Component manager wrappers.
bool Entity::addComponent(Component* component) {
	if (destroyed) return false;

	require(component != nullptr, "Entity, addComponent: component cant be null.");

	return components.addComponent(component);
}
bool Entity::removeComponent(Component* component) {
	if (destroyed) return false;

	require(component != nullptr, "Entity, removeComponent: component cant be null.");
	
	return components.removeComponent(component);
}
bool Entity::containsComponent(const Component* const component) const {
	if (destroyed) return false;

	require(component != nullptr, "Entity, containsComponent: component cant be null.");

	return components.containsComponent(component);
}

// Tag container wrappers.
bool Entity::unTag(const std::string& tag) {
	if (destroyed) return false;

	return tags.unTag(tag);
}
bool Entity::isTagged(const std::string& tag) const {
	if (destroyed) return false;

	return tags.isTagged(tag);
}
bool Entity::tag(const std::string& tag) {
	if (destroyed) return false;

	return tags.tag(tag);
}

bool Entity::isParentOf(const Entity* const child) {
	require(child != nullptr, "Entity, isParentOf: child cant be null.");
	
	return std::find(childs.begin(), childs.end(), child) != childs.end();
}
bool Entity::addChild(Entity* const child) {
	if (destroyed) return false;

	bool add = !isParentOf(child);

	if (add) {
		childs.push_back(child);
	}

	return add;
}
bool Entity::removeChild(Entity* const child) {
	if (destroyed) return false;

	bool remove = isParentOf(child);

	if (remove) {
		childs.remove(child);
	}

	return remove;
}

// Update all components that are enabled if entity is in enabled
// state, and is not destroyed.
void Entity::update() {
	if (!enabled || destroyed) {
		return;
	}

	components.update();

	if (childs.size() > 0) return;

	std::for_each(childs.begin(), childs.end(), [this](Entity* const e) {
		if (e->isDestroyed()) {
			childs.remove(e);
		}
	});
}

// Draw all components that are visible if entity is in enabled
// state, and is not destroyed.
void Entity::draw() {
	if (!visible || destroyed) {
		return;
	}

	components.draw();
}

std::list<Entity* const> Entity::getChilds() const {
	return childs;
}
#pragma endregion

Entity::~Entity() {
}
