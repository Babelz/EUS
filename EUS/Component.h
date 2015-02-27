#pragma once
#include <cassert>

class Game;
class Entity;

// Base class for all components.
class Component {
private:
	Game& game;
	Entity& owner;

	int updateOrder;

	bool destroyed;
	bool enabled;
	bool initialized;
protected:
	Game& getGame() const;
	Entity& getOwner() const;

	// Called every update if component is enabled.
	virtual void onUpdate(const float deltaTime);

	// Called when component gets destroyed.
	virtual void onDestroyed();

	// Called when enabled value changes.
	virtual void onEnabledChanged(const bool oldState, const bool newState);

	// Called when update order changes.
	virtual void updateOrderChanged(const int newOrder, const int oldOrder);

	// Called in first enable call.
	virtual void onInitialize();
public:
	int getUpdateOrder() const;

	Component(Game& game, Entity& owner, const int updateOrder = 0);

	void changeUpdateOrder(const int newOrder);

	void enable();
	void disable();
	bool isEnabled() const;

	void destroy();
	bool isDestroyed() const;

	void update(const float deltaTime);

	virtual ~Component();
};