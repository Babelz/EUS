#include "Component.h"

#pragma region Access routines
Entity* const Component::getOwner() const {
	return owner;
}

bool Component::isEnabled() const {
	return enabled;
}
bool Component::isDestroyed() const {
	return destroyed;
}

void Component::changeUpdateOrder(int newOrder) {
	if (newOrder != updateOrder) {
		int oldOrder = updateOrder;

		updateOrder = newOrder;

		updateOrderChanged(oldOrder, newOrder);
	}
}
#pragma endregion

Component::Component(Entity* const owner, int updateOrder) : owner(owner), updateOrder(updateOrder) {
	assert(owner != nullptr);
}

#pragma region Protected members
void Component::onUpdate() { }

void Component::onDestroyed() { }

void Component::onEnabledChanged(bool newEnabled, bool oldEnabled) { }

void Component::onInitialize() { }

void Component::updateOrderChanged(int newOrder, int oldOrder) { }
#pragma endregion

#pragma region Public members
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

void Component::destroy() {
	if (destroyed) {
		return;
	}

	destroyed = true;
	
	onDestroyed();
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
