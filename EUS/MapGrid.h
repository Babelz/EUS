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

	int parentXIndex, parentYIndex;

	int goalIndexX, goalIndexY;

	void calcG() {
		// Calc g.
	}
	void calcH() {
		// Calc h.
	}
public:
	Entity* const tile;

	const int xIndex;
	const int yIndex;

	NodeType nodeType;

	// TODO: astar stuff.

	MapNode(Entity* const tile, const int xIndex, const int yIndex) : tile(tile),
																	  xIndex(xIndex),
																	  yIndex(yIndex),
																	  parentXIndex(-1),
																	  parentYIndex(-1),
																	  goalIndexX(-1),
																	  goalIndexY(-1),
																	  h(0), 
																	  g(0),
																	  f(0),
																	  nodeType(NodeType::Passable) {
	}

	// TODO: getters for g, h, j.

	void setGoa(int x, int y) {
		goalIndexX = x;
		goalIndexY = y;
	}

	void update() {
		calcG();
		calcH();

		f = h + g;
	}
	void reset() {
		f = g = h = 0;
		parentXIndex = parentYIndex = -1;
		goalIndexX = goalIndexY = -1;
	}
};

class MapGrid : public Component {
private:
	std::vector<std::vector<MapNode>> nodes;
	
	TileEngine& tileEngine;
protected:
	void onInitialize();
public:
	MapGrid(Game& game, Entity& entity, TileEngine& tileEngine);
	
	MapNode& nodeAtIndex(int i, int j);

	~MapGrid();
};

