#include "AStarPathfinder.h"


AStarPathfinder::AStarPathfinder(Game& game, Entity& owner, MapGrid& grid) : Component(game, owner),
																			 grid(grid),
																			 skipCorners(false),
																			 hasStart(false),
																			 hasGoal(false) {
}

#pragma region Private members
bool AStarPathfinder::isWalkable(const int indexX, const int indexY, const std::vector<NodeInfo>& nodeInfos) {
	if (indexX >= grid.getWidth() || indexX < 0) return false;

	if (indexY >= grid.getHeight() || indexY < 0) return false;

	MapNode& node = grid.nodeAtIndex(indexY, indexX);
	
	for (size_t i = 0; i < nodeInfos.size(); i++) {
		if (node.getTileInfo()->getType() == nodeInfos[i].type) {
			return nodeInfos[i].passable;
		}
	}

	return false;
}
void AStarPathfinder::internalFindPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos, const pmath::Vec2f& start, const pmath::Vec2f& goal) {
	const size_t width = grid.getWidth();
	const size_t height = grid.getHeight();
	
	const int startX = static_cast<int>(start.x / grid.getNodeSize());
	const int startY = static_cast<int>(start.y / grid.getNodeSize());

	if (startX < 0 || startX >= grid.getWidth()) return;
	if (startY < 0 || startY >= grid.getHeight()) return;

	const int goalX = static_cast<int>(goal.x / grid.getNodeSize());
	const int goalY = static_cast<int>(goal.y / grid.getNodeSize());

	if (goalX < 0 || goalX >= grid.getWidth()) return;
	if (goalY < 0 || goalY >= grid.getHeight()) return;

	std::vector<MapNode*> openList;
	std::vector<MapNode*> closedList;

	MapNode* current = &grid.nodeAtIndex(startY, startX);
	openList.push_back(current);

	int currentX = static_cast<int>(current->getTile()->getTransform().getPosition().x);
	int currentY = static_cast<int>(current->getTile()->getTransform().getPosition().y);

	while (openList.size() > 0) {
		// At goal.
		if (currentX == goal.x && currentY == goal.y) {
			break;
		}

		closedList.push_back(current);

		std::vector<MapNode*> newNodes;

		const int x = currentX / grid.getNodeSize();
		const int y = currentY / grid.getNodeSize();

		// Top.
		if (isWalkable(x, y - 1, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(y - 1, x));
		}
		// Bottom.
		if (isWalkable(x, y + 1, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(y + 1, x));
		}
		// Right.
		if (isWalkable(x + 1, y, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(y, x + 1));
		}
		// Left.
		if (isWalkable(x - 1, y, nodeInfos)) {
			newNodes.push_back(&grid.nodeAtIndex(y, x - 1));
		}

		// TODO: implement.
		if (skipCorners) {
			throw std::logic_error("Not implemented - AStarPathfinder \"skipCorners\"");
		}

		openList.erase(std::remove(openList.begin(), openList.end(), current), openList.end());

		std::for_each(newNodes.begin(), newNodes.end(), [this, startX, startY, goalX, goalY, &closedList, &openList, &nodeInfos, &current] (MapNode* n) {
			// Node is in closed list, skip it.
			if (std::find(closedList.begin(), closedList.end(), n) != closedList.end()) {
				return;
			}

			// Set values for node.
			n->setStart(startX, startY);
			n->setGoal(goalX, goalY);
			
			// Set A mod, if node infos contain value for it.
			for (size_t i = 0; i < nodeInfos.size(); i++) {
				if (n->getTileInfo()->getType() == nodeInfos[i].type) {
					n->setA(nodeInfos[i].cost);
				}
			}

			// Node is in open list, check if its cheaper to move trough it.
			if (std::find(openList.begin(), openList.end(), n) != openList.end()) {
				if (n->getG() > current->getG()) {
					// Set child and calculate values.
					n->setChild(current->getXIndex(), current->getYIndex());
					n->update();
				}
			} else {
				// New node, add it to open list and set its parent index.
				n->setChild(current->getXIndex(), current->getYIndex());
				n->update();

				openList.push_back(n);
			}
		});

		// At goal or no path was found.
		if (openList.size() == 0) {
			break;
		} else {
			// Sort all nodes based on their total cost (F).
			std::sort(openList.begin(), openList.end(), [](MapNode* a, MapNode* b) {
				int aF = a->getF();
				int bF = b->getF();

				return aF < bF;
			});
		}

		current = openList[0];

		currentX = current->getTile()->getTransform().getPosition().x;
		currentY = current->getTile()->getTransform().getPosition().y;
	};

	foundPath = currentX == goal.x && currentY == goal.y;

	while (current->hasChild()) {
		extractVectorFrom(*current, outPath);
		
		MapNode* last = current;

		current = &grid.nodeAtIndex(current->getChildIndexY(), current->getChildIndexX());
		
		last->reset();
	}
	
	std::reverse(outPath.begin(), outPath.end());
}
void AStarPathfinder::extractVectorFrom(const MapNode& current, std::vector<pmath::Vec2f>& outPath) {
	outPath.push_back(pmath::Vec2f(current.getTile()->getTransform().getPosition().x,
								   current.getTile()->getTransform().getPosition().y));
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
