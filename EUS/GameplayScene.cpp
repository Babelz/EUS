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
	// Build the map.
	MapBuilder mapBuilder(getGame());
	// Each tile is 2 units in width and height.
	map = mapBuilder.buildModelMap("meshmap", 2, tiles);

	// Add tiles.
	for (size_t i = 0; i < tiles.size(); i++) {
		getEntities().addEntity(tiles[i]);
		//tiles[i]->hide();
	}
	
	getEntities().addEntity(map);

	// TODO: test input init.
	getGame().inputManager().bind("move l", [this](InputArgs& args) {
		getGame().view().setX(getGame().view().getX() - 0.05f);
	}, 1, new KeyTrigger(SDLK_LEFT));

	getGame().inputManager().bind("move r", [this](InputArgs& args) {
		getGame().view().setX(getGame().view().getX() + 0.05f);
	}, 1, new KeyTrigger(SDLK_RIGHT));

	getGame().inputManager().bind("move u", [this](InputArgs& args) {
		getGame().view().setY(getGame().view().getY() + 0.05f);
	}, 1, new KeyTrigger(SDLK_UP));

	getGame().inputManager().bind("move d", [this](InputArgs& args) {
		getGame().view().setY(getGame().view().getY() - 0.05f);
	}, 1, new KeyTrigger(SDLK_DOWN));

	getGame().inputManager().bind("rot x+", [this](InputArgs& args) {
		getGame().view().setRotX(getGame().view().getRotX() + 0.05f);
	}, 1, new KeyTrigger(SDLK_HOME));

	getGame().inputManager().bind("rot x-", [this](InputArgs& args) {
		getGame().view().setRotX(getGame().view().getRotX() - 0.05f);
	}, 1, new KeyTrigger(SDLK_END));

	getGame().inputManager().bind("rot y+", [this](InputArgs& args) {
		getGame().view().setRotY(getGame().view().getRotY() + 0.05f);
	}, 1, new KeyTrigger(SDLK_INSERT));

	getGame().inputManager().bind("rot y-", [this](InputArgs& args) {
		getGame().view().setRotY(getGame().view().getRotY() - 0.05f);
	}, 1, new KeyTrigger(SDLK_PAGEUP));

	getGame().inputManager().bind("res", [this](InputArgs& args) {
		getGame().view().setRotY(0.0f);
		getGame().view().setRotX(0.0f);
	}, 1, new KeyTrigger(SDLK_F1));

	EUSEntityBuilder b("jeesus", getGame());
	getEntities().addEntity(b.buildPlayer());
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
