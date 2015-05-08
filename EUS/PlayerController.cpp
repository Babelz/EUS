#include "PlayerController.h"
#include "TileEngine.h"

PlayerController::PlayerController(Game& game, Entity& owner) : Component(game, owner) {
}

#pragma region Private members
bool PlayerController::inBounds(const float nextX, const float nextY) {
	const float transformNextY = nextY == 0 ? nextY : -nextY;

	return nextX >= 0.0f && nextX < rightBound && 
		   transformNextY < bottomBound && transformNextY >= 0.0f;
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

	// Get bounds.
	Entity* map = getGame().sceneManager().getActiveScene().getEntities().findEntityWithTag("map");
	assert(map != nullptr);

	// Get engine.
	TileEngine* tileEngine = map->getComponent<TileEngine>();

	bottomBound = static_cast<float>(tileEngine->mapHeightInPixels());
	rightBound = static_cast<float>(tileEngine->mapWidthInPixels());
	const float tileSize = static_cast<float>(tileEngine->tileSize());

	inputManager.bind("move up", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY() + tileSize)) return;

		owner.getTransform().setY(owner.getTransform().getY() + 2.0f);
	}, 1, new KeyTrigger(SDLK_w));

	inputManager.bind("move down", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY() - tileSize)) return;

		owner.getTransform().setY(owner.getTransform().getY() - 2.0f);
	}, 1, new KeyTrigger(SDLK_s));

	inputManager.bind("move left", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX() - tileSize, owner.getTransform().getY())) return;

		owner.getTransform().setX(owner.getTransform().getX() - 2.0f);
	}, 1, new KeyTrigger(SDLK_a));

	inputManager.bind("move right", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX() + tileSize, owner.getTransform().getY())) return;

		owner.getTransform().setX(owner.getTransform().getX() + 2.0f);
	}, 1, new KeyTrigger(SDLK_d));
}

void PlayerController::onUpdate(const float deltaTime) {

}
#pragma endregion

PlayerController::~PlayerController() {
}
