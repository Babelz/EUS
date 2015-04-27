#include "GameplayScene.h"
#include "EUSEntityBuilder.h"
#include "ModelRenderer.h"
#include "ModelMapping.h"

GameplayScene::GameplayScene() : Scene("gameplay") {
}

static std::vector<Entity*> tiles;
static Entity* map;

#pragma region Protected members
void GameplayScene::onActivate() {
	MapBuilder mapBuilder(getGame());

	map = mapBuilder.buildModelMap("meshmap", 32, tiles);

	for (size_t i = 0; i < tiles.size(); i++){
		getEntities().addEntity(tiles[i]);
	}

	getEntities().addEntity(map);
}
#pragma endregion

#pragma region Public members
static float x = 0.f;
static float y = 0.f;
static float z = 0.f;
static float r = 0.f;

void GameplayScene::update(const float deltaTime) {
	getEntities().update(deltaTime);
	}
void GameplayScene::draw(const float deltaTime)  {
	getEntities().draw(deltaTime);
}
#pragma endregion

GameplayScene::~GameplayScene() {
}
