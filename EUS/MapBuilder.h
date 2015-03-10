#pragma once
#include "AStarPathfinder.h"
#include "SpriteRenderer.h"
#include "NamedTileSheet.h"
#include "EntityBuilder.h"
#include "SheetMapping.h"
#include "TileBuilder.h"
#include "MapLoader.h"
#include "TileEngine.h"

class MapBuilder : public EntityBuilder {
public:
	MapBuilder(Game& game);

	Entity* buildMap(const std::string& name, const std::string& sheetName, size_t tileSize, std::vector<Entity*>& outTiles) const;

	~MapBuilder();
};

