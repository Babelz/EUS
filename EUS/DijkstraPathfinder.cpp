#include "DijkstraPathfinder.h"

DijkstraPathfinder::DijkstraPathfinder(Game& game, Entity& owner, MapGrid& grid) : Component(game, owner),
																				   grid(grid) {
}

#pragma region Private members
bool DijkstraPathfinder::isWalkable(const int nextX, const int nextY, const std::list<NodeInfo>& nodeInfos) const {
	// Overlaps the grid, cant walk here.
	if (nextX >= grid.getWidth() || nextX < 0) return false;
	if (nextY >= grid.getHeight() || nextY < 0) return false;

	// Check the node.
	MapNode& node = grid.nodeAtIndex(nextY, nextX);

	// Node is occupied, cant walk here.
	if (node.hasEntity()) return false;
	
	// Check if the user can walk in this given terrain type.
	for (NodeInfo n : nodeInfos) {
		if (n.type == node.getTileInfo()->getType()) {
			return n.passable;
		}
	}

	// Invalid results, cant walk here it seems.
	return false;
}
DijkstarNode DijkstraPathfinder::createNewNode(const DijkstarNode& parent) const {
	DijkstarNode n;

	n.x = parent.x;
	n.y = parent.y;
	n.cost = parent.cost + 1;

	return n;
}
#pragma endregion

#pragma region Public members
void DijkstraPathfinder::findPath(std::vector<DijkstarNode>& outPath, const std::list<NodeInfo>& nodeInfos, const int startX, const int startY, const int range) const {
	std::vector<DijkstarNode> openList;

	DijkstarNode start;
	start.x = startX;
	start.y = startY;

	openList.push_back(start);

	while (openList.size() > 0) {
		DijkstarNode current = openList[0];
		openList.erase(openList.begin());
		
		outPath.push_back(current);

		if (current.cost > range) continue;;

		if (current.x >= 0 && current.x < grid.getWidth() &&
			current.y >= 0 && current.y < grid.getHeight()) {

			// Next left.
			const int nl = current.x - 1;
			// Next right.
			const int nr = current.x + 1;

			// Next top.
			const int nt = current.y - 1;
			// Next bottom.
			const int nb = current.y + 1;

			// Left.
			if (isWalkable(nl, current.y, nodeInfos)) {
				DijkstarNode n = createNewNode(current);

				n.parentIndex = outPath.size() - 1;
				n.x = nl;

				openList.push_back(n);
			}

			// Right.
			if (isWalkable(nr, current.y, nodeInfos)) {
				DijkstarNode n = createNewNode(current);

				n.parentIndex = outPath.size() - 1;
				n.x = nr;

				openList.push_back(n);
			}

			// Top.
			if (isWalkable(current.x, nt, nodeInfos)) {
				DijkstarNode n = createNewNode(current);

				n.parentIndex = outPath.size() - 1;
				n.y = nt;

				openList.push_back(n);
			}

			// Bottom.
			if (isWalkable(current.x, nb, nodeInfos)) {
				DijkstarNode n = createNewNode(current);

				n.parentIndex = outPath.size() - 1;
				n.y = nb;

				openList.push_back(n);
			}
		}
	}
}
#pragma endregion

DijkstraPathfinder::~DijkstraPathfinder() {
}
