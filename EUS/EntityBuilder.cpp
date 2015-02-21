#include "EntityBuilder.h"

EntityBuilder::EntityBuilder(const std::string& name, Game& game) : m_name(name),
																    m_game(game) {
}

#pragma region Protected members
Game& EntityBuilder::game() const {
	return m_game;
}
#pragma endregion

#pragma region Public members
const std::string& EntityBuilder::name() const {
	return m_name;
}
#pragma endregion

EntityBuilder::~EntityBuilder() {
}
