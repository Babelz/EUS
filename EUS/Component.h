#pragma once
#include <cassert>

class Entity;

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
	virtual void onEnabledChanged(bool newEnabled, bool oldEnabled);

	// Called when update order changes.
	virtual void updateOrderChanged(int newOrder, int oldOrder);

	// Called in first enable call.
	virtual void onInitialize();
public:
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