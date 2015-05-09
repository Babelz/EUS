#pragma once
// TODO: shitty. Split this file.
#include "AStarPathfinder.h"

class DijkstarNode {
public:
	int parentIndex;

	int x;
	int y;
	
	int cost;

	DijkstarNode() : x(0), y(0), cost(1), parentIndex(0) { };
	~DijkstarNode() { };
};

class DijkstraPathfinder : public Component {
private:
	MapGrid& grid;
	
	bool isWalkable(const int nextX, const int nextY, const std::list<NodeInfo>& nodeInfos) const;
	DijkstarNode createNewNode(const DijkstarNode& parent) const;
public:
	DijkstraPathfinder(Game& game, Entity& owner, MapGrid& grid);
	
	void findPath(std::vector<DijkstarNode>& outPath, const std::list<NodeInfo>& nodeInfos, const int startX, const int startY, const int range) const;
	
	~DijkstraPathfinder();
};

