#include "GameplayScene.h"

GameplayScene::GameplayScene() : Scene("gameplay") {
}

static Entity* map;
static Entity* e;

#pragma region Protected members
void GameplayScene::onActivate() {
	e = new Entity();

	Sprite* s = new Sprite(getGame().content().load<Texture>("tuksu"));
	s->setZ(1.0f);
	s->setScale(0.25f);

	SpriteRenderer* r = new SpriteRenderer(getGame(), *e, s);
	r->enable();
	r->show();

	e->addComponent(r);

	e->getTransform().setPosition(glm::vec3(128.0f, 128.0f, 1.0f));
	e->enable();
	e->show();
	
	MapBuilder builder(getGame());
	
	std::vector<Entity*> tiles;
	map = builder.buildMap("test", "bordersheet", 64, tiles);

	getEntities().addEntity(map);

	for (size_t i = 0; i < tiles.size(); i++){
		getEntities().addEntity(tiles[i]);
	}

	getEntities().addEntity(e);

}
#pragma endregion

#pragma region Public members
void GameplayScene::update(const float deltaTime) {
	getEntities().update(deltaTime);
}
void GameplayScene::draw(const float deltaTime)  {
	getEntities().draw(deltaTime);

	std::vector<pmath::Vec2f> path;
	AStarPathfinder* p = map->getComponent<AStarPathfinder>();

	std::vector<NodeInfo> infos;

	infos.push_back(NodeInfo(true, TileType::Plains, 1));

	bool found = false;
	
	int x, y;
	SDL_GetMouseState(&x, &y);

	p->findPath(found, path, infos, pmath::Vec2f(x, y), pmath::Vec2f(384.0f, 384.0f));

	if (found) {
		for (size_t i = 0; i < path.size(); i++) {
			getGame().spriteBatch().draw(getGame().content().load<Texture>("tuksu"), pmath::Rectf(path[i].x, path[i].y, 64, 64));
		}
	}
}
#pragma endregion

GameplayScene::~GameplayScene() {
}
