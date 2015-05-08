#include "GameplayScene.h"
#include "EUSEntityBuilder.h"
#include "ModelRenderer.h"
#include "ModelMapping.h"
#include "MapGrid.h"

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

	// TODO: debug.
	// Insert units to the map.
	EUSEntityBuilder entityBuilder("entitybuilder", getGame());
	getEntities().addEntity(entityBuilder.buildPlayer());


	// Bounds of the debug map
	// min x, y = 0
	// max x = 16 units
	// max y = -8 units
	// 1 tile = 2 units
	
	// Create player units.
	Entity* p1Rifleman1 = entityBuilder.buildRifleman("player");
	p1Rifleman1->getTransform().setZ(0.45f);
	p1Rifleman1->getTransform().setY(-8.0);

	Entity* p1Rifleman2 = entityBuilder.buildRifleman("player");
	p1Rifleman2->getTransform().setZ(0.45f);
	p1Rifleman2->getTransform().setY(-8.0);
	p1Rifleman2->getTransform().setX(2.0);

	Entity* p1Rifleman3 = entityBuilder.buildRifleman("player");
	p1Rifleman3->getTransform().setZ(0.45f);
	p1Rifleman3->getTransform().setY(-6.0);
	
	// Add entities and register them to the grid.
	getEntities().addEntity(p1Rifleman1);
	getEntities().addEntity(p1Rifleman2);
	getEntities().addEntity(p1Rifleman3);

	// Register entities.
	MapGrid* grid = map->getComponent<MapGrid>();
	grid->nodeAtIndex(4, 0).setEntity(p1Rifleman1);
	grid->nodeAtIndex(4, 1).setEntity(p1Rifleman2);
	grid->nodeAtIndex(3, 0).setEntity(p1Rifleman3);
	grid->printEntityMappings();
	grid->printTiles();

	// Center the map.
	// TODO: calculate it. 
	getGame().view().setX(7.85f);
	getGame().view().setY(-3.75f);

	// TODO: test input init for the camera.
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

		getGame().view().setX(7.85f);
		getGame().view().setY(-3.75f);
	}, 1, new KeyTrigger(SDLK_F1));
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
