#include "BorderTileBuilder.h"

BorderTileBuilder::BorderTileBuilder() {
}

#pragma region Protected memberss
Entity* BorderTileBuilder::createFlats() const {
	Entity* tile = new Entity();

	TileInfo* info = new TileInfo(*tile, "flats", 0, 0, TileType::Flats);
	info->enable();

	tile->addComponent(info);

	return tile;
}
Entity* BorderTileBuilder::createHills() const {
	Entity* tile = new Entity();

	TileInfo* info = new TileInfo(*tile, "hill", 0, 3, TileType::Hills);
	info->enable();

	tile->addComponent(info);

	return tile;
}

void BorderTileBuilder::createBuilders() {
	pushBuilder("plains", createFlats);
}
#pragma endregion

BorderTileBuilder::~BorderTileBuilder() {
}
