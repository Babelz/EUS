#pragma once
#include "TileBuilder.h"
#include "Components.h"
#include "MapLoader.h"
#include "Sheets.h"

class EntityBuilder {
private:
	void buildMap(Entity* const entity, TileBuilder& tileBuilder, SheetMapping& mappings, NamedTileSheet& sheet, MapLoader& data) const;
public:
	EntityBuilder();
	
	Entity* borderMap(Game& game) const;
	Entity* tile(Game& game) const;

	~EntityBuilder();
};

