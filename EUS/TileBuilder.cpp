#include "TileBuilder.h"

TileBuilder::TileBuilder(Game& game) : EntityBuilder("", game) {
	
	// p stands for player. Add p1, p2, p3 etc if needed.
	pushBuilder("pFactory", std::function<Entity*()>(std::bind(&TileBuilder::createPlayerFactory, this)));
	pushBuilder("pCity", std::function<Entity*()>(std::bind(&TileBuilder::createPlayerCity, this)));
	
	// cpu...
	pushBuilder("cpu1Factory", std::function<Entity*()>(std::bind(&TileBuilder::createCPU1Factory, this)));
	pushBuilder("cpu1City", std::function<Entity*()>(std::bind(&TileBuilder::createCPU1City, this)));
	pushBuilder("cpu1HQ", std::function<Entity*()>(std::bind(&TileBuilder::createCPU1HQ, this)));

	// n stands for neutral.
	pushBuilder("nFactory", std::function<Entity*()>(std::bind(&TileBuilder::createNeutralFactory, this)));
	pushBuilder("nCity", std::function<Entity*()>(std::bind(&TileBuilder::createNeutralCity, this)));

	pushBuilder("woods", std::function<Entity*()>(std::bind(&TileBuilder::createWoods, this)));
	pushBuilder("hBridge", std::function<Entity*()>(std::bind(&TileBuilder::createBridge, this)));
	pushBuilder("vBridge", std::function<Entity*()>(std::bind(&TileBuilder::createBridge, this)));

	// TODO: fix.
	// OH GOD PLEASE FIX THIS BS.
	// Shittiest gode EU, make these from array or smthng.
	
	static const std::string coasts [] = {
		"bfCoast", "tfCoast", "rCoast",
		"lCoast", "brcCoast", "blcCoast",
		"trcCoast", "tlcCoast"
	};

	static const std::string corners [] = {
		"rightPartTop", "leftPartTop", "leftPartBottom",
		"rightPartBottom"
	};

	for (size_t i = 0; i < sizeof(coasts) / sizeof(std::string); i++) {
		pushBuilder(coasts[i], std::function<Entity*()>(std::bind(&TileBuilder::createCoast, this)));
	}

	for (size_t i = 0; i < sizeof(corners) / sizeof(std::string); i++) {
		pushBuilder(corners[i], std::function<Entity*()>(std::bind(&TileBuilder::createCoast, this)));
	}

	// TODO: fix, not a HQ tile.
	pushBuilder("playerHQ", std::function<Entity*()>(std::bind(&TileBuilder::createPlayerHQ, this)));

	//pushBuilder("trcCoast", std::function<Entity*()>(std::bind(&TileBuilder::createCoast, this)));

	pushBuilder("plains", std::function<Entity*()>(std::bind(&TileBuilder::createPlains, this)));
	pushBuilder("hills", std::function<Entity*()>(std::bind(&TileBuilder::createHills, this)));
	pushBuilder("sea", std::function<Entity*()>(std::bind(&TileBuilder::createSea, this)));
}

#pragma region Private members
Entity* TileBuilder::internalCreateTile(const std::string& name, const int movementCost, const int coverValue, const TileType type) const {
	Entity* tile = new Entity();

	TileInfo* tileInfo = new TileInfo(game(), *tile, name, movementCost, coverValue, type);
	tile->addComponent(tileInfo);
	tileInfo->enable();

	return tile;
}

// Methods for creating tiles that player "owns".
Entity* TileBuilder::createPlayerFactory() const {
	Entity* tile = internalCreateTile("pFactory", 0, 4, TileType::Urban);
	tile->tag("p");

	return tile;
}
Entity* TileBuilder::createPlayerCity() const {
	Entity* tile = internalCreateTile("pCity", 0, 4, TileType::Urban);
	tile->tag("p");

	return tile;
}
Entity* TileBuilder::createPlayerHQ() const {
	Entity* tile = internalCreateTile("playerHQ", 0, 5, TileType::Urban);
	tile->tag("p");

	return tile;
}

// Methods for creating tiles that CPU1 "owns".
Entity* TileBuilder::createCPU1Factory() const {
	Entity* tile = internalCreateTile("cpu1Factory", 0, 4, TileType::Urban);
	tile->tag("cpu1");

	return tile;
}
Entity* TileBuilder::createCPU1City() const {
	Entity* tile = internalCreateTile("cpu1City", 0, 4, TileType::Urban);
	tile->tag("cpu1");

	return tile;
}
Entity* TileBuilder::createCPU1HQ() const {
	Entity* tile = internalCreateTile("cpu1HQ", 0, 4, TileType::Urban);
	tile->tag("cpu1");

	return tile;
}

// Methods for creating tiles that are neutral.
Entity* TileBuilder::createNeutralFactory() const {
	Entity* tile = internalCreateTile("nFactory", 0, 4, TileType::Urban);
	tile->tag("n");

	return tile;
}
Entity* TileBuilder::createNeutralCity() const {
	Entity* tile = internalCreateTile("nCity", 0, 4, TileType::Urban);
	tile->tag("n");

	return tile;
}

Entity* TileBuilder::createBridge() const {
	return internalCreateTile("bridge", 0, 0, TileType::Bridge);
}
Entity* TileBuilder::createCoast() const {
	return internalCreateTile("coast", 0, 0, TileType::Plains);
}
Entity* TileBuilder::createWoods() const {
	return internalCreateTile("woods", 3, 4, TileType::Woods);
}

Entity* TileBuilder::createPlains() const {
	return internalCreateTile("plains", 0, 0, TileType::Plains);
}
Entity* TileBuilder::createHills() const {
	return internalCreateTile("hill", 0, 3, TileType::Hills);
}
Entity* TileBuilder::createSea() const {
	return internalCreateTile("sea", 0, 0, TileType::Water);
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

	require(iter._Ptr != nullptr, "TileBuilder, buildTile: builder with name '" + name + "' does not exist");

	if (iter._Ptr != nullptr) {
		return iter._Ptr->_Myval.builder();
	}

	return nullptr;
}

// TODO: used with model maps, hacks hacks... Time is short.
Entity* TileBuilder::buildTile(const char ch) const {
	switch (ch) {
	case '#':
		return createPlains();
	case 'p':
		return createSea();
	default:
		throw std::logic_error("TileBuilder: unsupported tile token");
	}

	return nullptr;
}
#pragma endregion

TileBuilder::~TileBuilder() {
}
