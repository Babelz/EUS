#pragma once
#include "Entity.h"
#include "Game.h"
#include "MapGrid.h"
#include "Enums.h"

struct NodeInfo {
	// Readonly fields.
	const bool passable;
	const TileType type;
	const size_t cost;

	NodeInfo(const bool passable, const TileType type, const size_t cost) : passable(passable),
																			type(type),
																		    cost(cost) {
	}
};

class AStarPathfinder : public Component {
private:
	pmath::Vec2f start;
	pmath::Vec2f goal;
	
	// Flags.
	bool skipCorners;
	bool hasStart;
	bool hasGoal;

	MapGrid& grid;

	bool isWalkable(const int indexX, const int indexY, const std::vector<NodeInfo>& nodeInfos);
	void internalFindPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos, const pmath::Vec2f& start, const pmath::Vec2f& goal);
	void extractVectorFrom(const MapNode& current, std::vector<pmath::Vec2f>& outPath);
public:
	AStarPathfinder(Game& game, Entity& owner, MapGrid& grid);

	const bool getSkripCorners() const;
	void setSkripCorners(const bool value);

	pmath::Vec2f getGoal() const;
	void setGoal(const pmath::Vec2f& goal);
	void resetGoal();

	pmath::Vec2f getStart() const;
	void setStart(const pmath::Vec2f& start);
	void resetStart();

	void reset();

	// Finds path, sets start and goal.
	void findPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos, const pmath::Vec2f& start, const pmath::Vec2f& goal);
	// Finds path. Start and goal must be set via mutators.
	void findPath(bool& foundPath, std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos);
	// Finds path. Start and goal must be set via mutators.
	void findPath(std::vector<pmath::Vec2f>& outPath, const std::vector<NodeInfo>& nodeInfos);

	~AStarPathfinder();
};

