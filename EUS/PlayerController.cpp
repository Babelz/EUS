#include "PlayerController.h"
#include "TileEngine.h"
#include "MapGrid.h"
#include "MovementSpaceHandler.h"

PlayerController::PlayerController(Game& game, Entity& owner) : Component(game, owner) {
}

#pragma region Private members
bool PlayerController::inBounds(const float nextX, const float nextY) {
	const float transformNextY = nextY == 0 ? nextY : -nextY;

	return nextX >= 0.0f && nextX < rightBound && 
		   transformNextY < bottomBound && transformNextY >= 0.0f;
}
// Handle interactions.
void PlayerController::interact() {
	// Calculate index.
	const int column = static_cast<int>(getOwner().getTransform().getX() / 2.0f);
	const int row = std::abs(static_cast<int>(getOwner().getTransform().getY() / 2.0f));

	// Should be inbounds so we can skip all bounding checks.
	// Just get the grid and find node at given index.
	Entity* map = getGame().sceneManager().getActiveScene().getEntities().findEntityWithTag("map");
	MapGrid* grid = map->getComponent<MapGrid>();

	MapNode& node = grid->nodeAtIndex(row, column);

	// Node has no entity to interact with, just return.
	if (!node.hasEntity()) return;

	// Handle entities by their tags.
	Entity* entity = node.getEntity();

	if (entity->isTagged("unit")) interactWithUnit(entity);
}
void PlayerController::interactWithUnit(Entity* unit) {
	selectedUnit = unit;

	MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();

	handler->changeSelectedUnit(unit);
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

	MovementSpaceHandler* handler = new MovementSpaceHandler(getGame(), getOwner(), tileEngine->mapWidthInTiles(), tileEngine->mapHeightInTiles(), *map->getComponent<MapGrid>());
	handler->enable();

	owner.addComponent(handler);

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

	inputManager.bind("interact", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY())) return;

		// TODO: handle interactions.
		interact();
	}, 1, new KeyTrigger(SDLK_e));

	inputManager.bind("deselect", [&owner, this, tileSize](InputArgs& args) {
		if (args.state != InputState::PRESSED || !inBounds(owner.getTransform().getX(), owner.getTransform().getY())) return;

		selectedUnit = nullptr;
	}, 1, new KeyTrigger(SDLK_r));
}

void PlayerController::onUpdate(const float deltaTime) {

}
#pragma endregion

PlayerController::~PlayerController() {
}
