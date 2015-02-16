#include "EntityBuilder.h"
#include "MapLoader.h"
#include "SpriteRenderer.h"

EntityBuilder::EntityBuilder() {
}

#pragma region Public members
Entity* EntityBuilder::borderMap(Game& game, const std::string& filename) const {
	MapLoader loader;
	loader.load(filename);

	Entity* map = new Entity();

	

	for (size_t i = 0; i < loader.getMapHeight(); i++) {
		for (size_t j = 0; j < loader.getMapWidth(); j++) {
			char ch = loader.charAt(i, j);
		}
	}

	return map;
}
Entity* EntityBuilder::tile(Game& game) const {
	Entity* tile = new Entity();

	//SpriteRenderer renderer = new SpriteRenderer(game, tile);

	return tile;
}
#pragma endregion

EntityBuilder::~EntityBuilder() {
}
