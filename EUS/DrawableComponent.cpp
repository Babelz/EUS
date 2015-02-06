#include "DrawableComponent.h"

DrawableComponent::DrawableComponent(Entity& owner, int updateOrder, int drawOrder) 
: Component(owner, updateOrder), drawOrder(drawOrder) {
	visible = true;
}

#pragma region Protected members
void DrawableComponent::onDraw() {
}

void DrawableComponent::onVisibleChanged(bool newVisibility, bool oldVisibility) {
}

void DrawableComponent::drawOrderChanged(int newOrder, int oldOrder) {
}
#pragma endregion 

#pragma region Public members
int DrawableComponent::getDrawOrder() const {
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
bool DrawableComponent::isVisible() const {
	return visible;
}

void DrawableComponent::draw() {
	if (!visible || isDestroyed()) {
		return;
	}

	onDraw();
}
#pragma endregion 

DrawableComponent::~DrawableComponent() {

}