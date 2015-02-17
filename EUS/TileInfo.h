#pragma once
#include <string>
#include "Entity.h"
#include "Resources.h"

enum TileType {
	Flats,
	Hills,
	Water
};

class TileInfo : public Component {
private:	
	int movementCost;
	int coverValue;

	std::string name;	
	TileType type;
public:
	TileInfo(Entity& owner, const std::string& name, const int movementCost, const int coverValue, const TileType type);

	int getMovementCost() const;
	int getCoverValue() const;

	const std::string& getName() const;
	TileType getType();

	~TileInfo();
};

