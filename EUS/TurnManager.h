#pragma once
#include "EntityManager.h"
#include "PlayerController.h"

class TurnManager {
private:
	TurnManager();

	EntityManager* entities;

	Entity* player1;
	Entity* player2;
	Entity* playerInTurn;

	PlayerController* p1;
	PlayerController* p2;
	PlayerController* current;

	std::vector<Entity*> movedUnits;
public:
	static TurnManager& instance() {
		static TurnManager m;

		return m;
	}

	TurnManager(const TurnManager& t) = delete;
	void operator =(const TurnManager& t) = delete;

	void setEntities(EntityManager* entities);
	void changeTurn();
	bool canMove(Entity* e);
	void registerUnit(Entity* e);

	~TurnManager();
};

