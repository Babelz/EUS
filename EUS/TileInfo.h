#pragma once
#include <string>
#include "Entity.h"
#include "Resources.h"

enum TileType
{
	Flats,
	Hills,
	Water
};

class TileInfo : public Component {
private:
	TileType type;
	
	int movementCost;
	int coverValue;

	std::string name;	
public:
	TileInfo(Entity& owner, const std::string& name, const int movementCost, const int coverValue, const TileType type);

	std::string& getName();
	
	int getMovementCost() const;
	int getCoverValue() const;
	
	TileType getType();

	~TileInfo();
};

