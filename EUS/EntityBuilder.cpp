#include "EntityBuilder.h"
#include "BorderTileBuilder.h"

EntityBuilder::EntityBuilder() {
}

#pragma region Private members
void EntityBuilder::buildMap(Entity* const entity, TileBuilder& tileBuilder, SheetMapping& mappings, NamedTileSheet& sheet, MapLoader& data) const {
	tileBuilder.initialize();
	mappings.initialize();
	sheet.initialize();
	
	for (size_t i = 0; i < data.getMapHeight(); i++) {
		for (size_t j = 0; j < data.getMapWidth(); j++) {

		}
	}
}
#pragma endregion

#pragma region Public members
Entity* EntityBuilder::borderMap(Game& game) const {
	const std::string filename = std::string("Content\\test.txt");
	
	MapLoader loader;
	loader.load(filename);

	Entity* map = new Entity();

	Texture* texture = game.content().load<Texture>("bordersheet");

	BorderTileBuilder tileBuilder;
	BorderMappings mappings;
	BorderSheet sheet(texture, 32);

	buildMap(map, tileBuilder, mappings, sheet, loader);

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
