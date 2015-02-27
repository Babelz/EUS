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
	
	// Methods for creating tiles that player "owns".
	Entity* createPlayerFactory() const;
	Entity* createPlayerCity() const;
	
	// Methods for creating tiles that CPU1 "owns".
	Entity* createCPU1Factory() const;
	Entity* createCPU1City() const;

	// Methods for creating tiles that are neutral.
	Entity* createNeutralFactory() const;
	Entity* createNeutralCity() const;

	Entity* createBridge() const;
	Entity* createCoast() const;
	Entity* createWoods() const;

	Entity* createPlains() const;
	Entity* createHills() const;
	Entity* createEntity() const;
	Entity* createSea() const;
	
	void pushBuilder(const std::string& tileName, std::function<Entity*()> builder);
public:
	TileBuilder(Game& game);

	Entity* buildTile(const std::string& name) const;

	~TileBuilder();
};

