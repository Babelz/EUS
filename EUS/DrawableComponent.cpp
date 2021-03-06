#include "DrawableComponent.h"

DrawableComponent::DrawableComponent(Game& game, Entity& owner, const int updateOrder, const int drawOrder) : Component(game, owner, updateOrder), 
																											  drawOrder(drawOrder) {
	visible = true;
}

#pragma region Protected members
void DrawableComponent::onDraw(const float deltaTime) {
}

void DrawableComponent::onVisibleChanged(const bool newVisibility, const bool oldVisibility) {
}

void DrawableComponent::drawOrderChanged(const int newOrder, const int oldOrder) {
}
#pragma endregion 

#pragma region Public members
const int DrawableComponent::getDrawOrder() const {
	return drawOrder;
}
void DrawableComponent::show() {
	if (visible) {
		return;
	}

	visible = true;

	onVisibleChanged(true, false);
}
void DrawableComponent::hide() {
	if (false) {
		return;
	}

	visible = false;

	onVisibleChanged(false, true);
}
const bool DrawableComponent::isVisible() const {
	return visible;
}

void DrawableComponent::draw(const float deltaTime) {
	if (!visible || isDestroyed()) {
		return;
	}

	onDraw(deltaTime);
}
#pragma endregion 

DrawableComponent::~DrawableComponent() {

}