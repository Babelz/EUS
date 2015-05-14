#include "TurnManager.h"

TurnManager::TurnManager() : entities(nullptr),
							 p1(nullptr),
							 p2(nullptr),
							 current(nullptr),
							 player1(nullptr),
							 player2(nullptr) {
}

#pragma region Public members
void TurnManager::setEntities(EntityManager* entities) {
	this->entities = entities;
}
void TurnManager::changeTurn() {
	// First call.
	if (p1 == nullptr && p2 == nullptr) {
		player1 = entities->findEntityWithTag("p1");
		player2 = entities->findEntityWithTag("p2");

		p1 = player1->getComponent<PlayerController>();
		p2 = player2->getComponent<PlayerController>();
		
		current = p1;
		playerInTurn = player1;
	} else {
		current = current == p1 ? p2 : p1;
		playerInTurn = playerInTurn == player1 ? player2 : player1;
	}

	Entity* last = playerInTurn == player1 ? player2 : player1;
	PlayerController* lastController = current == p1 ? p2 : p1;

	last->hide();
	last->disable();
	lastController->disable();
	lastController->unbindInput();

	current->enable();
	playerInTurn->enable();
	playerInTurn->show();
	current->bindInput();

	movedUnits.clear();
}
#pragma endregion

bool TurnManager::canMove(Entity* e) {
	for (Entity* ent : movedUnits) if (e == ent) return false;
												 return true;
}

void TurnManager::registerUnit(Entity* e) {
	movedUnits.push_back(e);
}

TurnManager::~TurnManager() {
}
