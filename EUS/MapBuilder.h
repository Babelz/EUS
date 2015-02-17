#pragma once
#include "EntityBuilder.h"

class MapBuilder : public EntityBuilder {
public:
	MapBuilder(const std::string& name, Game& game);
	
	~MapBuilder();
};

