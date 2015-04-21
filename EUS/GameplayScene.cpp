#include "GameplayScene.h"
#include "EUSEntityBuilder.h"
#include "ModelRenderer.h"

GameplayScene::GameplayScene() : Scene("gameplay") {
}

static Entity* map;
static Entity* player;
static ModelRenderer* r;
static Entity* e;

#pragma region Protected members
void GameplayScene::onActivate() {
	MapBuilder mapBuilder(getGame());

	std::vector<Entity*> tiles;
	map = mapBuilder.buildMap("test", "bordersheet", 64, tiles);

	//getEntities().addEntity(map);

	for (size_t i = 0; i < tiles.size(); i++){
		//getEntities().addEntity(tiles[i]);
	}

	//EUSEntityBuilder entityBuilder("entities", getGame());
	//player = entityBuilder.buildPlayer();

	//getEntities().addEntity(player);

	e = new Entity();
	Model* m = getGame().content().load<Model>("box");
	m->setTexture(getGame().content().load<Texture>("tuksu"));
	
	r = new ModelRenderer(getGame(), *e, m);
	r->enable();

	e->getTransform().setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}
#pragma endregion

#pragma region Public members
static float rot = 0.0f;

void GameplayScene::update(const float deltaTime) {
	getEntities().update(deltaTime);
}
void GameplayScene::draw(const float deltaTime)  {
	r->draw(deltaTime);
}
#pragma endregion

GameplayScene::~GameplayScene() {
}
