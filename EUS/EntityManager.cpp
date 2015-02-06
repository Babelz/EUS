#include "EntityManager.h"

EntityManager::EntityManager() {
}

#pragma region Public memebers
void EntityManager::addEntity(Entity* const entity) {
}
void EntityManager::removeEntity(Entity* const entity) {
}

std::vector<Entity* const> EntityManager::findEntitiesWithTag(const std::string& tag) const {
	return std::vector<Entity* const>();
}

Entity* const EntityManager::findEntityWithTag(const std::string& tag) const {
	return nullptr;
}
Entity* const EntityManager::findEntityWithID(int id) const {
	return nullptr;
}

void EntityManager::update() {
}
void EntityManager::draw() {
}
#pragma endregion

void EntityManager::freeEntities(){
}

EntityManager::~EntityManager() {
}