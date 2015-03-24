#include "UnitInformation.h"

UnitInformation::UnitInformation(Game& game, Entity& owner,
							     const std::list<TileType>& walkableTerrainTypes, 
								 const DamageType damageType,
								 const ArmorType armorType,
								 const OrganicUnit organicUnit,
								 const int movementRange,
								 const float addedDefence,
								 const float addedDamage) : walkableTerrainTypes(walkableTerrainTypes),
														    armorType(armorType),
															damageType(damageType),
															organicUnit(organicUnit),
															movementRange(movementRange),
															addedDefence(addedDefence),
															addedDamage(addedDamage),
															Component(game, owner) {
}

#pragma region Protected members
void UnitInformation::onInitialize() {
}
#pragma endregion

#pragma region Public memebers
const float UnitInformation::getHitPoints() const {
	return hitPoints;
}

void UnitInformation::takeDamageFrom(DamageType damageType, const float enemyAddedDamage) {
	switch (damageType) {
		case Light:
			break;
		case Piercing:
			break;
		case Explosive:
			break;
		default:
			break;
	}
}
const float UnitInformation::dealDamageTo(ArmorType armorType, const float enemyAddedArmor) {
	return 0.0f;
}

const bool UnitInformation::alive() const {
	return false;
}
#pragma endregion

UnitInformation::~UnitInformation() {
}
