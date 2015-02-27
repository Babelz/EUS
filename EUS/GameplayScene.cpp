#include "GameplayScene.h"

GameplayScene::GameplayScene() : Scene("gameplay") {
}

#pragma region Protected members
void GameplayScene::onActivate() {
	MapBuilder builder(getGame());
	std::vector<Entity*> tiles;

	Entity* map = builder.buildMap("test", "bordersheet", 64, tiles);

	getEntities().addEntity(map);

	for (size_t i = 0; i < tiles.size(); i++){
		getEntities().addEntity(tiles[i]);
	}
}
#pragma endregion

#pragma region Public members
void GameplayScene::update(const float deltaTime) {
	getEntities().update(deltaTime);
}
void GameplayScene::draw(const float deltaTime)  {
	getEntities().draw(deltaTime);
}
#pragma endregion

GameplayScene::~GameplayScene() {
}
