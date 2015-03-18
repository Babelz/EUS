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

	const bool hasGoal() const;
	const bool hasStart() const;
public:
	MapNode(Entity* const tile, const int xIndex, const int yIndex);
	MapNode();

	const bool hasChild() const;

	TileInfo* const getTileInfo() const;
	Entity* const getTile() const;

	// Modifier value for randomizing the path.
	void setA(const int value);
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
	
	const int width;
	const int height;
	const int nodeSize;
protected:
	void onInitialize();
public:
	MapGrid(Game& game, Entity& entity, const int width, const int height, const int nodeSize);
	
	MapNode& nodeAtIndex(const int i, const int j);

	const int getWidth() const;
	const int getHeight() const;
	const int getNodeSize() const;

	~MapGrid();
};

