#pragma once
#include "EntityBuilder.h"
#include "PlayerCursor.h"

class EUSEntityBuilder : public EntityBuilder {
public:
	EUSEntityBuilder(const std::string& name, Game& game);

	Entity* buildPlayer(const std::string& name) const;
	// Creates new rifleman. Tag can be "p1" or "p2".
	Entity* buildRifleman(const std::string& ownerTag) const;

	~EUSEntityBuilder();
};

