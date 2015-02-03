#include "Component.h"

Component::Component(Entity* const owner, int updateOrder) : owner(owner), updateOrder(updateOrder) {
	assert(owner != nullptr);

	destroyed = false;
	enabled = false;
	initialized = false;
}

#pragma region Protected members
Entity* const Component::getOwner() const {
	return owner;
}

void Component::onUpdate() { }

void Component::onDestroyed() { }

void Component::onEnabledChanged(bool oldState, bool newState) { }

void Component::onInitialize() { }

void Component::updateOrderChanged(int newOrder, int oldOrder) { }
#pragma endregion

#pragma region Public members
int Component::getUpdateOrder() const {
	return updateOrder;
}
void Component::changeUpdateOrder(int newOrder) {
	if (newOrder != updateOrder) {
		int oldOrder = updateOrder;

		updateOrder = newOrder;

		updateOrderChanged(oldOrder, newOrder);
	}
}

void Component::enable() {
	// Do initialization if this is the first
	// call to enable.
	if (!enabled && !initialized) {
		onInitialize();

		initialized = true;
		enabled = true;

		return;
	}

	if (enabled) {
		return;
	}

	enabled = true;

	onEnabledChanged(true, false);
}
void Component::disable() {
	if (!enabled) {
		return;
	}

	enabled = false;

	onEnabledChanged(false, true);
}
bool Component::isEnabled() const {
	return enabled;
}

void Component::destroy() {
	if (destroyed) {
		return;
	}

	destroyed = true;
	
	onDestroyed();
}
bool Component::isDestroyed() const {
	return destroyed;
}

void Component::update() {
	if (!enabled || destroyed) {
		return;
	}

	onUpdate();
}
#pragma endregion

Component::~Component() {
}
