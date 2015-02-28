#pragma once
#include "Entity.h"
#include <string>
#include <list>
#include <vector>

class EntityManager {
private:
	std::list<Entity* const> entities;

	// Query buffer.
	std::vector<Entity* const> findResults;

	// Keep destroyed entities here. Remove entities 
	// next frame and release memory.
	std::list<Entity* const> destroyedEntities;
	
	void freeEntities();
public:
	EntityManager();

	const bool addEntity(Entity* const entity);
	const bool removeEntity(Entity* const entity);
	const bool containsEntity(const Entity* const entity) const;

	std::vector<Entity* const>& findEntitiesWithTag(const std::string& tag);
	
	Entity* const findEntityWithTag(const std::string& tag) const;
	Entity* const findEntityWithID(const int id) const;

	void update(const float deltaTime);
	void draw(const float deltaTime);

	~EntityManager();
};

