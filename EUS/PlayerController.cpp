#include "PlayerController.h"
#include "TileEngine.h"

PlayerController::PlayerController(Game& game, Entity& owner) : Component(game, owner) {
}

#pragma region Private members
bool PlayerController::inBounds(const float nextX, const float nextY) {
	return nextX >= 0.0f && nextX < rightBound && nextY >= 0.0f && nextY < bottomBound;
}
#pragma endregion

#pragma region Protected members
void PlayerController::onDestroyed() {
}

void PlayerController::onInitialize() {
	// Input init.
	cursor = getOwner().getComponent<PlayerCursor>();

	assert(cursor != nullptr);

	InputManager& inputManager = getGame().inputManager();
	Entity& owner = getOwner();

	inputManager.bind("move up", [&owner, this](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY() - 64.0f)) return;

		owner.getTransform().setY(owner.getTransform().getY() - 64.0f);
	}, 1, new KeyTrigger(SDLK_w));

	inputManager.bind("move down", [&owner, this](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY() + 64.0f)) return;

		owner.getTransform().setY(owner.getTransform().getY() + 64.0f);
	}, 1, new KeyTrigger(SDLK_s));

	inputManager.bind("move left", [&owner, this](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX() - 64.0f, owner.getTransform().getY())) return;

		owner.getTransform().setX(owner.getTransform().getX() - 64.0f);
	}, 1, new KeyTrigger(SDLK_a));

	inputManager.bind("move right", [&owner, this](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX() + 64.0f, owner.getTransform().getY())) return;

		owner.getTransform().setX(owner.getTransform().getX() + 64.0f);
	}, 1, new KeyTrigger(SDLK_d));

	// Get bounds.
	Entity* map = getGame().sceneManager().getActiveScene().getEntities().findEntityWithTag("map"); 
	assert(map != nullptr);

	TileEngine* tileEngine = map->getComponent<TileEngine>();

	bottomBound = static_cast<float>(tileEngine->mapHeightInPixels());
	rightBound = static_cast<float>(tileEngine->mapWidthInPixels());
}

void PlayerController::onUpdate(const float deltaTime) {

}
#pragma endregion

PlayerController::~PlayerController() {
}
