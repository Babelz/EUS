#include "TileInfo.h"

TileInfo::TileInfo(Entity& owner,
				   const std::string& name, 
				   const int movementCost,  
				   const int coverValue, 
				   const TileType type) : name(name),
										  movementCost(movementCost),
										  coverValue(coverValue),
										  type(type),
										  Component(owner) {
}

#pragma region Public members
const std::string& TileInfo::getName() const {
	return name;
}

int TileInfo::getMovementCost() const {
	return movementCost;
}
int TileInfo::getCoverValue() const {
	return coverValue;
}

TileType TileInfo::getType() {
	return type;
}
#pragma endregion

TileInfo::~TileInfo() {
}
