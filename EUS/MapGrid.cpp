#include "MapGrid.h"

#pragma region MapNode class
MapNode::MapNode(Entity* const tile, const size_t xIndex, const size_t yIndex) : tile(tile),
																			     xIndex(xIndex),
																			     yIndex(yIndex),
																				 childXIndex(-1),
																				 childYIndex(-1),
																				 goalIndexX(-1),
																				 goalIndexY(-1),
																				 h(0),
																				 g(0),
																				 f(0),
																				 a(0) {
	tileInfo = tile->getComponent<TileInfo>();

	assert(tileInfo != nullptr);
}
MapNode::MapNode() : MapNode(nullptr, 0, 0) {
}

#pragma region Private members
void MapNode::calcG() {
}
void MapNode::calcH() {
}
#pragma endregion

#pragma region Public members 
TileInfo* const MapNode::getTileInfo() const {
	return tileInfo;
}
Entity* const MapNode::getTile() const {
	return tile;
}

const bool MapNode::hasChild() const {
	return childXIndex > 0 && childYIndex > 0;
}
const bool MapNode::hasGoal() const {
	return goalIndexX > 0 && goalIndexY > 0;
}

void MapNode::setA(const int value) {
	a = value;
}
const int MapNode::getA() const {
	return a;
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

	f = h + g + a;
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
MapGrid::MapGrid(Game& game, Entity& entity, const size_t width, const size_t height, const size_t nodeSize) : Component(game, entity),
																											   width(width),
																											   height(height),																											   nodeSize(nodeSize) {
}

#pragma region Protected members
void MapGrid::onInitialize() {
	std::list<Entity* const> tiles = getOwner().getChilds();

	for (size_t i = 0; i < height; i++) {
		nodes.push_back(std::vector<MapNode>(width));
	}

	size_t i = 0;
	size_t j = 0;

	std::for_each(tiles.begin(), tiles.end(), [this, &i, &j](Entity* const e) {
		if (j >= width) {
			j = 0;
			i++;
		}

		MapNode node(e, j, i);
		nodes[i][j] = node;

		j++;
	});
}
#pragma endregion

#pragma region Public members
MapNode& MapGrid::nodeAtIndex(const size_t i, const size_t j) {
	return nodes[i][j];
}
#pragma endregion

MapGrid::~MapGrid() {
}
#pragma endregion
