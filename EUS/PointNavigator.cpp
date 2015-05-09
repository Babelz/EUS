#include "PointNavigator.h"

PointNavigator::PointNavigator(Game& game, Entity& owner) : Component(game, owner),
															navigating(false),
															index(0) {
}

#pragma region Private members
pmath::Vec2f PointNavigator::getOwnerLocation() const {
	return pmath::Vec2f(getOwner().getTransform().getX(), getOwner().getTransform().getY());
}

const bool PointNavigator::isAt(const pmath::Vec2f& location) const {
	using namespace pmath;

	Vec2f ownerLoc = getOwnerLocation();

	// std::cout << "DIST: " << (Vec2f::distance(ownerLoc, location)) << std::endl;

	return Vec2f::distance(ownerLoc, location) < 0.05f;
}

bool PointNavigator::atDestination() const {
	return isAt(destination);
}
bool PointNavigator::atCurrent() const {
	return isAt(current);
}

void PointNavigator::nextPoint() {
	current = points[index];
	index++;

	pmath::Vec2f ownerLoc = getOwnerLocation();

	velocity = (current - ownerLoc).normalized() * 4.5f;

	std::cout << "NEXT PT" << std::endl;
}
#pragma endregion


#pragma region Protected members
void PointNavigator::onUpdate(const float deltaTime) {
	if (!navigating) return;
	
	if (atDestination()) {
		navigating = false;

		callback(&getOwner());

		return;
	} else if (atCurrent()) {
		nextPoint();
	}

	Vector3 loc = getOwner().getTransform().getPosition();

	getOwner().getTransform().setX(loc.x + velocity.x * deltaTime);
	getOwner().getTransform().setY(loc.y + velocity.y * deltaTime);
}
#pragma endregion

#pragma region Public members
void PointNavigator::beginNavigate(std::function<void(Entity* const)> callback, std::vector<pmath::Vec2f>& points) {
	assert(!navigating);
	navigating = true;

	this->callback = callback;
	this->points = points;

	index = 0;
	destination = pmath::Vec2f(points.back());

	nextPoint();
}
#pragma endregion

PointNavigator::~PointNavigator() {
}
