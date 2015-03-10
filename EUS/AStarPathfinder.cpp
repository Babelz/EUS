#include "AStarPathfinder.h"


AStarPathfinder::AStarPathfinder(Game& game, Entity& owner, MapGrid& grid) : Component(game, owner),
																			 grid(grid),
																			 skipCorners(false),
																			 hasStart(false),
																			 hasGoal(false) {
}

#pragma region Private members
bool AStarPathfinder::isWalkable(const size_t indexX, const size_t indexY, const std::vector<NodeInfo>& nodeInfos) {
	// Stay in the deim grid son!
	assert(indexX >= 0 && indexX < grid.getWidth());
	assert(indexY >= 0 && indexY < grid.getHeight());

	MapNode& node = grid.nodeAtIndex(indexX, indexY);
	
	for (size_t i = 0; i < nodeInfos.size(); i++) {
		if (node.getTileInfo()->getType() == nodeInfos[i].type) {
			return nodeInfos[i].passable;
		}
	}

	throw std::logic_error("Unsupported tile type.");
}
void AStarPathfinder::internalFindPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos, const pmath::Vec2f& start, const pmath::Vec2f& goal) {
	const size_t width = grid.getWidth();
	const size_t height = grid.getHeight();
	
	const int startX = static_cast<int>(start.x / grid.getNodeSize());
	const int startY = static_cast<int>(start.y / grid.getNodeSize());

	const int goalX = static_cast<int>(goal.x / grid.getNodeSize());
	const int goalY = static_cast<int>(goal.y / grid.getNodeSize());

	std::vector<MapNode* const> openList;
	std::vector<MapNode* const> closedList;

	MapNode& current = grid.nodeAtIndex(startX, startY);

	while (true) {
		float currentX = current.getTile()->getTransform().getPosition().x;
		float currentY = current.getTile()->getTransform().getPosition().y;
		
		// At goal.
		if (currentX == goal.x && currentY == goal.y) {
			break;
		}

		std::vector<MapNode*> newNodes;

		const size_t x = static_cast<size_t>(currentX / grid.getNodeSize());
		const size_t y = static_cast<size_t>(currentY / grid.getNodeSize());

		// Top.
		if (isWalkable(x, y - 1, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(x, y - 1));
		}
		// Bottom.
		if (isWalkable(x, y + 1, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(x, y + 1));
		}
		// Right.
		if (isWalkable(x + 1, y, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(x + 1, y));
		}
		// Left.
		if (isWalkable(x - 1, y, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(x - 1, y));
		}

		// TODO: implement.
		if (skipCorners) {
			throw std::logic_error("Not implemented - AStarPathfinder \"skipCorners\"");
		}

		for (size_t i = 0; i < newNodes.size(); i++) {
			// Node is in closed list, skip it.

			// Node is in open list, check if its cheaper to move trough it.

			// New node, add it to open list and set its parent index.

		}
	}

	// Get surrounding nodes.
	// Set modifier value (A)
	// Set goal
	// Update nodes
	// Get best one
}
#pragma endregion

#pragma region Public members
const bool AStarPathfinder::getSkripCorners() const {
	return skipCorners;
}
void AStarPathfinder::setSkripCorners(const bool value) {
	skipCorners = value;
}

pmath::Vec2f AStarPathfinder::getGoal() const {
	return goal;
}
void AStarPathfinder::setGoal(const pmath::Vec2f& goal) {
	this->goal = goal;
}
void AStarPathfinder::resetGoal() {
	if (!hasGoal) return;

	hasGoal = false;

	goal = pmath::Vec2f(0.0f);
}

pmath::Vec2f AStarPathfinder::getStart() const {
	return start;
}
void AStarPathfinder::setStart(const pmath::Vec2f& start) {
	this->start = start;

	hasStart = true;
}
void AStarPathfinder::resetStart() {
	if (!hasStart) return;
	
	hasStart = false;

	// Reset vector? Sense?
	start = pmath::Vec2f(0.0f);
}

void AStarPathfinder::reset() {
	resetStart();
	resetGoal();
}

void AStarPathfinder::findPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos, const pmath::Vec2f& start, const pmath::Vec2f& goal) {
	internalFindPath(foundPath, outPath, nodeInfos, start, goal);
}
void AStarPathfinder::findPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos) {
	assert(hasGoal && hasStart);

	internalFindPath(foundPath, outPath, nodeInfos, start, goal);
}
void AStarPathfinder::findPath(std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos) {
	assert(hasGoal && hasStart);

	bool foundPath = false;

	internalFindPath(foundPath, outPath, nodeInfos, start, goal);
}
#pragma endregion

AStarPathfinder::~AStarPathfinder() {
}
