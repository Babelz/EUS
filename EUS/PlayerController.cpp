#include "PlayerController.h"
#include "TileEngine.h"
#include "MapGrid.h"
#include "MovementSpaceHandler.h"
#include "PointNavigator.h"
#include "TurnManager.h"
#include "UnitActionControl.h"
#include "UnitInformation.h"

PlayerController::PlayerController(Game& game, Entity& owner, const std::string& name) : Component(game, owner), name(name) {
}

#pragma region Private members
bool PlayerController::inBounds(const float nextX, const float nextY) {
	const float transformNextY = nextY == 0.0f ? nextY : -nextY;

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

	// Check if unit is selected.
	MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();

	if (handler->hasUnitSelected()) {
		// Unit is selected, check if it can be moved to given location.
		Entity* entity = handler->getSelectedUnit();
		
		if (handler->canMoveTo(column, row)) {
			// Generate point map and start moving the unit.
			std::vector<pmath::Vec2f> pointMap;
			handler->generatePointMapTo(pointMap, column, row);
			handler->hide();
			
			cursor->hide();
			unbindInput();

			// Move the unit.
			PointNavigator* navigator = entity->getComponent<PointNavigator>();

			const float oldX = entity->getTransform().getX();
			const float oldY = entity->getTransform().getY();

			navigator->beginNavigate([this, column, row, grid, oldX, oldY](Entity* const e) {
				e->getTransform().setX(column * 2.0f);
				e->getTransform().setY(-row * 2.0f);

				UnitActionControl* u = getOwner().getComponent<UnitActionControl>();
				u->computeActions(*grid, *e, name == "p1" ? "p2" : "p1");
				u->show();
				u->enable();
				u->bindInput();

				u->setAttackCallback([this, u, grid, row, column, oldX, oldY]() {
					u->unbindInput();

					bindInput();

					pmath::Vec2i attackVector = u->getAttackVector();

					Entity* enemy = grid->nodeAtIndex(attackVector.y, attackVector.x).getEntity();

					UnitInformation* a = enemy->getComponent<UnitInformation>();
					assert(a != nullptr);

					UnitInformation* b = selectedUnit->getComponent<UnitInformation>();
					assert(b != nullptr);

					getOwner().getComponent<PlayerCursor>()->enable();
					getOwner().getComponent<PlayerCursor>()->show();

					a->takeDamageFrom(b->getDamageType(), b->getAddedDamage());

					if (!a->alive()) {
						const int x = static_cast<int>(enemy->getTransform().getX() / 2.0f);
						const int y = static_cast<int>(std::fabs(enemy->getTransform().getY() / 2.0f));

						grid->nodeAtIndex(y, x).setEntity(nullptr);
						
						enemy->destroy();
						
						std::cout << "Enemy died" << std::endl;
					} else {
						std::cout << "Enemys health: " << static_cast<int>(a->getHitPoints()) << "/10" << std::endl;

					}

					u->hide();
					u->disable();

					MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();

					grid->nodeAtIndex(static_cast<int>(std::fabs(oldY / 2.0f)), static_cast<int>(oldX / 2.0f)).setEntity(nullptr);
					grid->nodeAtIndex(row, column).setEntity(selectedUnit);

					TurnManager::instance().registerUnit(selectedUnit);

					selectedUnit = nullptr;

					handler->changeSelectedUnit(nullptr);
					handler->show();

					handler->show();
				});

				u->setCancelCallback([this, u, grid, row, column, oldX, oldY]() {
					u->unbindInput();

					bindInput();

					getOwner().getComponent<PlayerCursor>()->enable();
					getOwner().getComponent<PlayerCursor>()->show();

					MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();
					handler->changeSelectedUnit(nullptr);
					handler->show();

					selectedUnit->getTransform().setX(oldX);
					selectedUnit->getTransform().setY(oldY); 

					selectedUnit = nullptr;

					u->hide();
					u->disable();
				});

				u->setMoveCallback([this, u, grid, row, column, oldX, oldY]() {
					u->unbindInput();

					bindInput();

					getOwner().getComponent<PlayerCursor>()->enable();
					getOwner().getComponent<PlayerCursor>()->show();
					MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();

					grid->nodeAtIndex(static_cast<int>(std::fabs(oldY / 2.0f)), static_cast<int>(oldX / 2.0f)).setEntity(nullptr);
					grid->nodeAtIndex(row, column).setEntity(selectedUnit);
					
					TurnManager::instance().registerUnit(selectedUnit);

					selectedUnit = nullptr;

					handler->changeSelectedUnit(nullptr);
					handler->show();

					u->hide();
					u->disable();
				});
			}, pointMap);

			//entity->getTransform().setX(column * 2.0f); entity->getTransform().setY(-row * 2.0f);

			return;
		}
	}

	// Node has no entity to interact with, just return.
	if (!node.hasEntity()) return;

	// Handle entities by their tags.
	Entity* entity = node.getEntity();

	// Interact with unit.
	if (entity->isTagged("unit") && entity->isTagged(name) && TurnManager::instance().canMove(entity)) {
		selectedUnit = entity;

		MovementSpaceHandler* handler = getOwner().getComponent<MovementSpaceHandler>();

		handler->changeSelectedUnit(entity);
	}
}
#pragma endregion

#pragma region Protected members
void PlayerController::onDestroyed() {
}

void PlayerController::bindInput() {
	InputManager& inputManager = getGame().inputManager();

	// Get bounds.
	Entity* map = getGame().sceneManager().getActiveScene().getEntities().findEntityWithTag("map");
	assert(map != nullptr);

	// Get engine.
	TileEngine* tileEngine = map->getComponent<TileEngine>();

	bottomBound = static_cast<float>(tileEngine->mapHeightInPixels());
	rightBound = static_cast<float>(tileEngine->mapWidthInPixels());
	const float tileSize = static_cast<float>(tileEngine->tileSize());

	Entity& owner = getOwner();

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

void PlayerController::unbindInput() {
	InputManager& inputManager = getGame().inputManager();
	inputManager.unbind("move up");
	inputManager.unbind("move down");
	inputManager.unbind("move left");
	inputManager.unbind("move right");
	inputManager.unbind("interact");
	inputManager.unbind("deselect");
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

	MovementSpaceHandler* handler = new MovementSpaceHandler(getGame(), getOwner(), *map->getComponent<MapGrid>());
	handler->enable();

	owner.addComponent(handler);
}

void PlayerController::onUpdate(const float deltaTime) {

}
#pragma endregion

PlayerController::~PlayerController() {
}
