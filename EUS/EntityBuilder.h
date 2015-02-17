#pragma once
#include "Game.h"

class EntityBuilder {
private:
	std::string m_name;
	Game& m_game;
protected:
	Game& game() const;
public:
	EntityBuilder(const std::string& name, Game& game);

	const std::string& name() const;

	~EntityBuilder();
};

