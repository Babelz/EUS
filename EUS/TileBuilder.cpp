#include "TileBuilder.h"

TileBuilder::TileBuilder(const std::string& name, Game& game) : EntityBuilder(name, game) {
	pushBuilder("plains", std::function<Entity*()>(std::bind(&TileBuilder::createPlains, this)));
	pushBuilder("hills", std::function<Entity*()>(std::bind(&TileBuilder::createHills, this)));
	pushBuilder("factory", std::function<Entity*()>(std::bind(&TileBuilder::createFactory, this)));
	pushBuilder("sea", std::function<Entity*()>(std::bind(&TileBuilder::createSea, this)));
	pushBuilder("city", std::function<Entity*()>(std::bind(&TileBuilder::createCity, this)));
}

#pragma region Private members
Entity* TileBuilder::internalCreateTile(const std::string& name, const int movementCost, const int coverValue, const TileType type) const {
	Entity* tile = new Entity();

	TileInfo* tileInfo = new TileInfo(*tile, name, movementCost, coverValue, type);
	tile->addComponent(tileInfo);
	tileInfo->enable();

	return tile;
}
Entity* TileBuilder::createPlains() const {
	return internalCreateTile("flats", 0, 0, TileType::Flats);
}
Entity* TileBuilder::createHills() const {
	return internalCreateTile("hill", 0, 3, TileType::Hills);
}
Entity* TileBuilder::createFactory() const {
	return internalCreateTile("factory", 0, 3, TileType::Flats);
}
Entity* TileBuilder::createSea() const {
	return internalCreateTile("sea", 0, 0, TileType::Water);
}
Entity* TileBuilder::createCity() const {
	return internalCreateTile("city", 0, 3, TileType::Flats);
}

void TileBuilder::pushBuilder(const std::string& tileName, std::function<Entity*()> builder) {
	tileBuilders.push_back(TileBuilderData(tileName, builder));
}
#pragma endregion

#pragma region Public members
Entity* TileBuilder::buildTile(const std::string& name) const {
	auto iter = std::find_if(tileBuilders.begin(), tileBuilders.end(), [name](TileBuilderData data) {
								return data.tileName == name;
						 });

	if (iter._Ptr != nullptr) {
		return iter._Ptr->_Myval.builder();
	}

	return nullptr;
}
#pragma endregion

TileBuilder::~TileBuilder() {
}
