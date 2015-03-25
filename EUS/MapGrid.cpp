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
																				 a(0),
																				 startIndexX(-1),
																				 startIndexY(-1) {
	tileInfo = tile->getComponent<TileInfo>();

	assert(tileInfo != nullptr);
}
MapNode::MapNode() : tile(nullptr),
					 xIndex(0),
					 yIndex(0),
					 childXIndex(-1),
					 childYIndex(-1),
					 goalIndexX(-1),
					 goalIndexY(-1),
					 h(0),
					 g(0),
					 f(0),
					 a(0),
					 startIndexX(-1),
					 startIndexY(-1) {
}

#pragma region Private members
void MapNode::calcG() {
	if (childYIndex + 1 == yIndex || childYIndex - 1 == yIndex) {
		g = 10;
	} else if (childXIndex + 1 == xIndex || childXIndex - 1 == xIndex) {
		g = 10;
	}

	g = 14;
}
void MapNode::calcH() {
	int startX = std::min(goalIndexX, xIndex);
	int startY = std::min(goalIndexY, yIndex);

	int endX = std::max(goalIndexX, xIndex);
	int endY = std::max(goalIndexY, yIndex);

	h = ((endX - startX) + (endY - startY)) * 10;
}

const bool MapNode::hasGoal() const {
	return goalIndexX > 0 && goalIndexY > 0;
}
const bool MapNode::hasStart() const {
	return startIndexX > 0 && startIndexY > 0;
}
#pragma endregion

#pragma region Public members 
const bool MapNode::hasChild() const {
	return childXIndex > 0 && childYIndex > 0;
}
TileInfo* const MapNode::getTileInfo() const {
	return tileInfo;
}
Entity* const MapNode::getTile() const {
	return tile;
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

const int MapNode::getChildIndexX() const {
	return childXIndex;
}
const int MapNode::getChildIndexY() const {
	return childYIndex;
}

const int MapNode::getXIndex() const {
	return xIndex;
}
const int MapNode::getYIndex() const {
	return yIndex;
}

void MapNode::setChild(const int x, const int y) {
	childXIndex = x;
	childYIndex = y;
}
void MapNode::setGoal(const int x, const int y) {
	goalIndexX = x;
	goalIndexY = y;
}
void MapNode::setStart(const int x, const int y) {
	startIndexX = x;
	startIndexY = y;
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
	// -1 no start.
	startIndexX = startIndexY = -1;
}
#pragma endregion

MapNode::~MapNode() {
}
#pragma endregion

#pragma region MapGrid class
MapGrid::MapGrid(Game& game, Entity& entity, const int width, const int height, const int nodeSize) : Component(game, entity),
																								      width(width),
																								      height(height),																											   nodeSize(nodeSize) {
}

#pragma region Protected members
void MapGrid::onInitialize() {
	std::list<Entity* const> tiles = getOwner().getChilds();

	const size_t height_t = static_cast<size_t>(height);

	for (size_t i = 0; i < height_t; i++) {
		nodes.push_back(std::vector<MapNode>(width));
	}

	int i = 0;
	int j = 0;

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
MapNode& MapGrid::nodeAtIndex(const int i, const int j) {
	return nodes[i][j];
}

const int MapGrid::getWidth() const {
	return width;
}
const int MapGrid::getHeight() const {
	return height;
}
const int MapGrid::getNodeSize() const {
	return nodeSize;
}
#pragma endregion

MapGrid::~MapGrid() {
}
#pragma endregion
