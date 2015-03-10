#pragma once
#include <string>
#include "Entity.h"
#include "Resources.h"

enum TileType {
	Plains,
	Hills,
	Water,
	Urban,
	Bridge,
	Coast,
	Woods
};

class TileInfo : public Component {
private:	
	int movementCost;
	int coverValue;

	std::string name;	
	TileType type;
public:
	TileInfo(Game& game, Entity& owner, const std::string& name, const int movementCost, const int coverValue, const TileType type);

	int getMovementCost() const;
	int getCoverValue() const;

	const std::string& getName() const;
	TileType getType();

	~TileInfo();
};

