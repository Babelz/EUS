#pragma once
#include "Entity.h"
#include "SceneManager.h"

class EntityBuilder {
public:
	EntityBuilder();
	
	Entity* borderMap(Game& game, const std::string& filename) const;
	Entity* tile(Game& game) const;

	~EntityBuilder();
};

