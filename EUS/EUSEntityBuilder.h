#pragma once
#include "EntityBuilder.h"
#include "PlayerCursor.h"

class EUSEntityBuilder : public EntityBuilder {
public:
	EUSEntityBuilder(const std::string& name, Game& game);

	Entity* buildPlayer() const;
	// Creates new rifleman. Tag can be "cpu" or "player".
	Entity* buildRifleman(const std::string& ownerTag) const;

	~EUSEntityBuilder();
};

