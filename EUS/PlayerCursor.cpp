#include "PlayerCursor.h"

PlayerCursor::PlayerCursor(Game& game, Entity& owner) : DrawableComponent(game, owner) {
}

#pragma region Protected members
void PlayerCursor::onInitialize() {
}

void PlayerCursor::onUpdate(const float deltaTime) {
}
void PlayerCursor::onDraw(const float deltaTime) {
}
#pragma endregion

PlayerCursor::~PlayerCursor() {
}
