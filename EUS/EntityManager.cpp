#include "EntityManager.h"

EntityManager::EntityManager() {
}

#pragma region Public memebers
void EntityManager::addEntity(Entity* entity) {
}
void EntityManager::removeEntity(Entity* entity) {
}

std::vector<Entity* const> EntityManager::findEntitiesWithTag(std::string tag) const {
	return std::vector<Entity* const>();
}

Entity* const EntityManager::findEntityWithTag(std::string tag) const {
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