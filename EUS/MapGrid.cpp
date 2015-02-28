#include "MapGrid.h"

#pragma region MapNode class
MapNode::MapNode(Entity* const tile, const int xIndex, const int yIndex) : tile(tile),
																		   xIndex(xIndex),
																		   yIndex(yIndex),
																		   childXIndex(-1),
																		   childYIndex(-1),
																		   goalIndexX(-1),
																		   goalIndexY(-1),
																		   h(0),
																		   g(0),
																		   f(0),
																		   nodeType(NodeType::Passable) {
}

#pragma region Private members
void MapNode::calcG() {
}
void MapNode::calcH() {
}
#pragma endregion

#pragma region Public members 
const NodeType MapNode::getType() const {
	return nodeType;
}

const bool MapNode::hasChild() const {
	return childXIndex > 0 && childYIndex > 0;
}
const bool MapNode::hasGoal() const {
	return goalIndexX > 0 && goalIndexY > 0;
}

const int MapNode::getG() const {
	return g;
}
const int MapNode::getH() const {
	return h;
}
const int MapNode::getF() const {
	return f;
}

void MapNode::setGoal(const int x, const int y) {
	goalIndexX = x;
	goalIndexY = y;
}

void MapNode::update() {
	calcG();
	calcH();

	f = h + g;
}
void MapNode::reset() {
	f = g = h = 0;
	// -1 = no parent.
	childXIndex = childYIndex = -1;
	// -1 no goal.
	goalIndexX = goalIndexY = -1;
}
#pragma endregion

MapNode::~MapNode() {
}

#pragma endregion


#pragma region MapGrid class
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
MapNode& MapGrid::nodeAtIndex(const int i, const int j) {
	return nodes[i][j];
}
#pragma endregion

MapGrid::~MapGrid() {
}
#pragma endregion
