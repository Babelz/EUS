#include "GameplayScene.h"
#include "EUSEntityBuilder.h"

GameplayScene::GameplayScene() : Scene("gameplay") {
}

static Entity* map;
static Entity* player;

#pragma region Protected members
void GameplayScene::onActivate() {
	MapBuilder mapBuilder(getGame());
	
	std::vector<Entity*> tiles;
	map = mapBuilder.buildMap("test", "bordersheet", 64, tiles);

	getEntities().addEntity(map);

	for (size_t i = 0; i < tiles.size(); i++){
		getEntities().addEntity(tiles[i]);
	}

	EUSEntityBuilder entityBuilder("entities", getGame());
	player = entityBuilder.buildPlayer();

	getEntities().addEntity(player);
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
