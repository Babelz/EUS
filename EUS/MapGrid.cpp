#include "MapGrid.h"

MapGrid::MapGrid(Game& game, Entity& entity, TileEngine& tileEngine) : Component(game, entity),
																	   tileEngine(tileEngine) {
}

#pragma region Protected members
void MapGrid::onInitialize() {
	std::list<Entity* const> tiles = getOwner().getChilds();

	for (size_t i = 0; i < tileEngine.mapHeightInTiles(); i++) {
		nodes.push_back(std::vector<MapNode>());
	}

	int i = 0;
	int j = 0;

	std::for_each(tiles.begin(), tiles.end(), [this, &i, &j](Entity* const e) {
		if (j >= tileEngine.mapWidthInTiles()) {
			j = 0;
			i++;
		}

		nodes[i].push_back(MapNode(e, i, j));
		
		j++;
	});
}
#pragma endregion

#pragma region Public members
MapNode& MapGrid::nodeAtIndex(int i, int j) {
	return nodes[i][j];
}
#pragma endregion

MapGrid::~MapGrid() {
}
