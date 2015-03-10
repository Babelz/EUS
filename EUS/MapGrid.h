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

	int startIndexX, startIndexY;
	int childXIndex, childYIndex;
	int goalIndexX, goalIndexY;
	int xIndex, yIndex;

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
	const bool hasStart() const;

	void setA(const int value);
	
	// TODO: your damn code son.

	// Modifier value.
	const int getA() const;
	// Movement cost G.
	const int getG() const;
	// H cost.
	const int getH() const;
	// Total cost.
	const int getF() const;

	const int getChildIndexX() const;
	const int getChildIndexY() const;
	
	const int getXIndex() const;
	const int getYIndex() const;

	void setChild(const int x, const int y);
	void setGoal(const int x, const int y);
	void setStart(const int x, const int y);
	void update();
	void reset();

	~MapNode();

	MapNode& operator = (const MapNode& other) {
		tile = other.tile;
		tileInfo = other.tileInfo;
		
		xIndex = other.xIndex;
		yIndex = other.yIndex;

		childXIndex = other.childXIndex;
		childYIndex = other.childYIndex;

		goalIndexX = other.goalIndexX;
		goalIndexY = other.goalIndexY;

		startIndexX = other.startIndexX;
		startIndexY = other.startIndexY;
		
		h = other.h;
		g = other.g;
		f = other.f;
		a = other.a;

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

