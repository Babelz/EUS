#pragma once
#include "TileEngine.h"
#include "Entity.h"
#include "TileBuilder.h"

// Class that wraps containing tile at index (coords) and 
// serves as astar node aswel.
class MapNode {
private:
	// A = additional cost.
	int h, g, f, a;

	int childXIndex, childYIndex;
	int goalIndexX, goalIndexY;
	size_t xIndex, yIndex;

	Entity* tile;
	TileInfo* tileInfo;

	void calcG();
	void calcH();
public:
	MapNode(Entity* const tile, const size_t xIndex, const size_t yIndex);
	MapNode();

	TileInfo* const getTileInfo() const;
	Entity* const getTile() const;

	const bool hasChild() const;
	const bool hasGoal() const;

	void setA(const int value);
	
	const int getA() const;
	const int getG() const;
	const int getH() const;
	const int getF() const;

	void setGoal(const int x, const int y);
	void update();
	void reset();

	~MapNode();

	MapNode& operator = (const MapNode& other) {
		tile = other.tile;
		
		xIndex = other.xIndex;
		yIndex = other.yIndex;

		childXIndex = other.childXIndex;
		childYIndex = other.childYIndex;

		goalIndexX = other.goalIndexX;
		goalIndexY = other.goalIndexY;
		
		h = other.h;
		g = other.g;
		f = other.f;

		return *this;
	}
};

class MapGrid : public Component {
private:
	std::vector<std::vector<MapNode>> nodes;
	
	const size_t width;
	const size_t height;
	const size_t nodeSize;
protected:
	void onInitialize();
public:
	MapGrid(Game& game, Entity& entity, const size_t width, const size_t height, const size_t nodeSize);
	
	MapNode& nodeAtIndex(const size_t i, const size_t j);

	const size_t getWidth() const;
	const size_t getHeight() const;
	const size_t getNodeSize() const;

	~MapGrid();
};

