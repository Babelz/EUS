#include "EUSEntityBuilder.h"

EUSEntityBuilder::EUSEntityBuilder(const std::string& name, Game& game) : EntityBuilder(name, game) {
}

#pragma region Public members
Entity* EUSEntityBuilder::buildPlayer() const {
	Entity* player = new Entity();

	PlayerCursor* cursor = new PlayerCursor(game(), *player);
	cursor->enable();

	player->addComponent(cursor);

	return player;
}
#pragma endregion

EUSEntityBuilder::~EUSEntityBuilder() {
}
