#pragma once
#include "TileEngine.h"
#include "Entity.h"

enum NodeType {
	Blocked,
	Passable
};

// Class that wraps containing tile at index (coords) and 
// serves as astar node aswel.
class MapNode {
private:
	int h, g, f;

	int childXIndex, childYIndex;
	int goalIndexX, goalIndexY;
	int xIndex, yIndex;

	Entity* const tile;

	NodeType nodeType;

	void calcG();
	void calcH();
public:

	MapNode(Entity* const tile, const int xIndex, const int yIndex);

	const NodeType getType() const;

	const bool hasChild() const;
	const bool hasGoal() const;

	const int getG() const;
	const int getH() const;
	const int getF() const;

	void setGoal(const int x, const int y);
	void update();
	void reset();

	~MapNode();
};

class MapGrid : public Component {
private:
	std::vector<std::vector<MapNode>> nodes;
	
	TileEngine& tileEngine;
protected:
	void onInitialize();
public:
	MapGrid(Game& game, Entity& entity, TileEngine& tileEngine);
	
	MapNode& nodeAtIndex(const int i, const int j);

	~MapGrid();
};

