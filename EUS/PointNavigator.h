#pragma once
#include "Entity.h"
#include <functional>

class PointNavigator : public Component {
private:
	bool navigating;

	std::function<void(Entity* const)> callback;

	// Current point index.
	int index;
	std::vector<pmath::Vec2f> points;
	
	pmath::Vec2f direction;
	pmath::Vec2f velocity;

	pmath::Vec2f current;
	pmath::Vec2f destination;

	pmath::Vec2f getOwnerLocation() const;

	const bool isAt(const pmath::Vec2f& location) const;

	bool atDestination() const;
	bool atCurrent() const;

	void nextPoint();
protected:
	void onUpdate(const float deltaTime) override;
public:
	PointNavigator(Game& game, Entity& owner);

	void beginNavigate(std::function<void(Entity* const)> callback, std::vector<pmath::Vec2f>& points);

	~PointNavigator();
};

