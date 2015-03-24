#include "EUSEntityBuilder.h"
#include "PlayerController.h"

EUSEntityBuilder::EUSEntityBuilder(const std::string& name, Game& game) : EntityBuilder(name, game) {
}

#pragma region Public members
Entity* EUSEntityBuilder::buildPlayer() const {
	Entity* player = new Entity();
	player->getTransform().setPosition(Vector3(256.0f, 256.0f, 0.0f));

	PlayerCursor* cursor = new PlayerCursor(game(), *player);
	cursor->enable();

	player->addComponent(cursor);

	PlayerController* controller = new PlayerController(game(), *player);
	controller->enable();

	player->addComponent(controller);

	return player;
}
#pragma endregion

EUSEntityBuilder::~EUSEntityBuilder() {
}
