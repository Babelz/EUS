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
Entity* EUSEntityBuilder::buildRifleman(const std::string& ownerTag) const {
	const static std::string CPU = std::string("cpu");
	const static std::string PLAYER = std::string("player");

	assert(ownerTag == CPU || ownerTag == PLAYER);

	Entity* rifleman = new Entity();

	rifleman->tag(ownerTag);

	return rifleman;
}
#pragma endregion

EUSEntityBuilder::~EUSEntityBuilder() {
}
