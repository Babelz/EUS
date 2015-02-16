#include "TileBuilder.h"

TileBuilder::TileBuilder() {
}

#pragma region Protected members
Entity* TileBuilder::createFactory() const {
	Entity* tile = new Entity();

	TileInfo* info = new TileInfo(*tile, "factory", 0, 3, TileType::Flats);
	info->enable();

	tile->addComponent(info);

	return tile;
}
Entity* TileBuilder::createSea() const {
	Entity* tile = new Entity();

	TileInfo* info = new TileInfo(*tile, "sea", 0, 0, TileType::Water);
	info->enable();

	tile->addComponent(info);

	return tile;
}
Entity* TileBuilder::createCity() const {
	Entity* tile = new Entity();

	TileInfo* info = new TileInfo(*tile, "city", 0, 3, TileType::Flats);
	info->enable();

	tile->addComponent(info);

	return tile;
}

void TileBuilder::pushBuilder(const std::string& tileName, std::function<Entity*()> builder) {
	tileDatas.push_back(TileBuilderData(tileName, builder));
}
#pragma endregion

#pragma region Public members
Entity* TileBuilder::buildTile(const std::string& name) const {
	auto iter = std::find_if(tileDatas.begin(), tileDatas.end(), [name](TileBuilderData data) {
								return data.tileName == name;
						 });

	if (iter._Ptr != nullptr) {
		return iter._Ptr->_Myval.builder();
	}

	return nullptr;
}

void TileBuilder::initialize() {
	createBuilders();

	assert(tileDatas.size() > 0);
}
#pragma endregion

TileBuilder::~TileBuilder() {
}
