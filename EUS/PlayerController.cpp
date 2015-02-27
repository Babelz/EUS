#include "PlayerController.h"

PlayerController::PlayerController(Game& game, Entity& owner, const int updateOrder) : Component(game, owner, updateOrder) {
}

#pragma region Protected members
void PlayerController::onDestroy() {
}

void PlayerController::onInitialize() {
}
#pragma endregion

PlayerController::~PlayerController() {
}
