#pragma once
#include "Entity.h"
#include "Enums.h"
#include <list>

class UnitInformation : public Component {
private:
	const std::list<TileType> walkableTerrainTypes;
	
	float hitPoints;

	// Added values. Used with special forces etc.
	const float addedDefence;
	const float addedDamage;

	const int movementRange;

	const DamageType damageType;
	const ArmorType armorType;
	const OrganicUnit organicUnit;
protected:
	void onInitialize() override;
public:
	UnitInformation(Game& game, Entity& owner,
					const std::list<TileType>& walkableTerrainTypes,
					const DamageType damageType,
					const ArmorType armorType,
					const OrganicUnit organicUnit,
					const int movementRange,
					const float addedDefence = 0.0f,
					const float addedDamage = 0.0f);
	
	const float getHitPoints() const;

	void takeDamageFrom(const DamageType damageType, const float enemyAddedDamage);
	const float dealDamageTo(const ArmorType armorType, const float enemyAddedArmor);

	const bool alive() const;

	~UnitInformation();
};

