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

	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);

	std::vector<Entity* const> findEntitiesWithTag(std::string tag) const;
	
	Entity* const findEntityWithTag(std::string tag) const;
	Entity* const findEntityWithID(int id) const;

	void update();
	void draw();

	void freeEntities();

	~EntityManager();
};

