#include "PlayerController.h"

PlayerController::PlayerController(Game& game, Entity& owner) : Component(game, owner) {
}

#pragma region Protected members
void PlayerController::onDestroyed() {
}

void PlayerController::onInitialize() {
	cursor = getOwner().getComponent<PlayerCursor>();

	assert(cursor != nullptr);
}

void PlayerController::onUpdate(const float deltaTime) {

}
#pragma endregion

PlayerController::~PlayerController() {
}
