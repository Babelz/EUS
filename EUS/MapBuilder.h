#pragma once
#include "SpriteRenderer.h"
#include "NamedTileSheet.h"
#include "EntityBuilder.h"
#include "SheetMapping.h"
#include "TileBuilder.h"
#include "MapLoader.h"

class MapBuilder : public EntityBuilder {
public:
	MapBuilder(Game& game);

	Entity* buildMap(const std::string& name, const std::string& sheetName, size_t tileSize) const;

	~MapBuilder();
};

