#pragma once
#include "EntityBuilder.h"
#include "Entity.h"
#include "TileInfo.h"
#include <string>
#include <list>

struct TileBuilderData {
	const std::string tileName;
	const std::function<Entity*()> builder;
	
	TileBuilderData(const std::string& tileName, std::function<Entity*()> builder) : tileName(tileName),
																		             builder(builder) {
	}
};

class TileBuilder : public EntityBuilder {
private:
	std::list<TileBuilderData> tileBuilders;

	Entity* internalCreateTile(const std::string& name, const int movementCost, const int coverValue, const TileType type) const;

	Entity* createPlains() const;
	Entity* createHills() const;
	Entity* createEntity() const;
	Entity* createFactory() const;
	Entity* createSea() const;
	Entity* createCity() const;

	void pushBuilder(const std::string& tileName, std::function<Entity*()> builder);
public:
	TileBuilder(const std::string& name, Game& game);

	Entity* buildTile(const std::string& name) const;

	~TileBuilder();
};

