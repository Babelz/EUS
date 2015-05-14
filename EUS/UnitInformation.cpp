#include "UnitInformation.h"

UnitInformation::UnitInformation(Game& game, Entity& owner,
								 const std::list<NodeInfo>& terrainInfos,
								 const DamageType damageType,
								 const ArmorType armorType,
								 const OrganicUnit organicUnit,
								 const int movementRange,
								 const float addedDefence,
								 const float addedDamage) : terrainInfos(terrainInfos),
														    armorType(armorType),
															damageType(damageType),
															organicUnit(organicUnit),
															movementRange(movementRange),
															addedDefence(addedDefence),
															addedDamage(addedDamage),
															hitPoints(10.0f),
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

void UnitInformation::takeDamageFrom(const DamageType damageType, const float enemyAddedDamage) {
	switch (damageType) {
		case Light:
			switch (armorType) {
			case Light:
				hitPoints -= (enemyAddedDamage + 3.0f);
				break;
			case Medium:
				hitPoints -= (enemyAddedDamage + 2.0f);
				break;
			case Heavy:
				hitPoints -= (enemyAddedDamage + 1.0f);
				break;
			default:
				break;
			}
			break;
		case Piercing:
			switch (armorType) {
			case Light:
				hitPoints -= (enemyAddedDamage + 7.0f);
				break;
			case Medium:
				hitPoints -= (enemyAddedDamage + 4.0f);
				break;
			case Heavy:
				hitPoints -= (enemyAddedDamage + 3.0f);
				break;
			default:
				break;
			}
			break;
		case Explosive:
			switch (armorType) {
			case Light:
				hitPoints -= (enemyAddedDamage + 9.0f);
				break;
			case Medium:
				hitPoints -= (enemyAddedDamage + 7.0f);
				break;
			case Heavy:
				hitPoints -= (enemyAddedDamage + 4.0f);
				break;
			default:
				break;
			}
			break;
		default:
			break;
	}
}
const float UnitInformation::dealDamageTo(const ArmorType armorType, const float enemyAddedArmor) {
	return 0.0f;
}

const std::list<NodeInfo>& UnitInformation::getTerrainInfos() const {
	return terrainInfos;
}

const bool UnitInformation::alive() const {
	return hitPoints > 0.0f;
}

const int UnitInformation::getMovementRange() const {
	return movementRange;
}

#pragma endregion

UnitInformation::~UnitInformation() {
}
