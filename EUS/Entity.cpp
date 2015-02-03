#include "Entity.h"

Entity::Entity() {
	visible = true;
	enabled = false;
	destroyed = false;

	position.x = 0.0f;
	position.y = 0.0f;
}

#pragma region Public members
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

	assert(component != nullptr);

	return components.addComponent(component);
}
bool Entity::removeComponent(Component* component) {
	if (destroyed) return false;

	assert(component != nullptr);
	
	return components.removeComponent(component);
}
bool Entity::containsComponent(Component* const component) const {
	if (destroyed) return false;

	assert(component != nullptr);

	return components.containsComponent(component);
}

// Tag container wrappers.
bool Entity::unTag(std::string tag) {
	if (destroyed) return false;

	return tags.unTag(tag);
}
bool Entity::isTagged(std::string tag) const {
	if (destroyed) return false;

	return tags.isTagged(tag);
}
bool Entity::tag(std::string tag) {
	if (destroyed) return false;

	return tags.tag(tag);
}

// Update all components that are enabled if entity is in enabled
// state, and is not destroyed.
void Entity::update() {
	if (!enabled || destroyed) {
		return;
	}

	components.update();
}

// Draw all components that are visible if entity is in enabled
// state, and is not destroyed.
void Entity::draw() {
	if (!visible || destroyed) {
		return;
	}

	components.draw();
}
#pragma endregion

Entity::~Entity() {
}
