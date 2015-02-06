#pragma once
#include "Entity.h"
#include <string>
#include <vector>

class EntityManager
{
private:
	std::list<Entity*> entities;
public:
	EntityManager();

	void addEntity(Entity* const entity);
	void removeEntity(Entity* const entity);

	std::vector<Entity* const> findEntitiesWithTag(const std::string& tag) const;
	
	Entity* const findEntityWithTag(const std::string& tag) const;
	Entity* const findEntityWithID(int id) const;

	void update();
	void draw();

	void freeEntities();

	~EntityManager();
};

