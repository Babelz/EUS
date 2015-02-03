#pragma once
#include <cassert>

class Entity;

// Base class for components that can update.
class Component {
private:
	Entity* const owner;

	int updateOrder;

	bool destroyed;
	bool enabled;
	bool initialized;
protected:
	Entity* const getOwner() const;

	// Called every update if component is enabled.
	virtual void onUpdate();

	// Called when component gets destroyed.
	virtual void onDestroyed();

	// Called when enabled value changes.
	virtual void onEnabledChanged(bool oldState, bool newState);

	// Called when update order changes.
	virtual void updateOrderChanged(int newOrder, int oldOrder);

	// Called in first enable call.
	virtual void onInitialize();
public:
	int getUpdateOrder() const;

	Component(Entity* const owner, int updateOrder = 0);

	void changeUpdateOrder(int newOrder);

	void enable();
	void disable();
	bool isEnabled() const;

	void destroy();
	bool isDestroyed() const;

	void update();

	virtual ~Component();
};