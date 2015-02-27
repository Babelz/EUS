#include "EUS.h"
#include "MapBuilder.h"

EUS::EUS() : Game() {
}

#pragma region Protected members
void EUS::onExit() { }

void EUS::onEvent(const SDL_Event& e) { }

static Entity* map;

void EUS::initialize() {
	texture = content().load<Texture>("tileset");
	
	MapBuilder b(*this);
	map = b.buildMap("test", "bordersheet", 32);
}

void EUS::update(float deltaTime) {
	map->update();
}

void EUS::draw(float deltaTime) {
	spriteBatch().begin();

	std::list<Entity* const> entities = map->getChilds();
	
	std::for_each(entities.begin(), entities.end(), [](Entity* const e) {
		Entity* entity = const_cast<Entity*>(e);

		entity->draw();
	});

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
