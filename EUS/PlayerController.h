#pragma once
#include "Entity.h"
#include "PlayerCursor.h"

class PlayerController : public Component {
private:
	Entity* selectedUnit;
	PlayerCursor* cursor;
	
	float bottomBound;
	float rightBound;

	bool inBounds(const float nextX, const float nextY);
	void interact();
	void interactWithUnit(Entity* unit);
protected:
	void onDestroyed() override;

	void onInitialize() override;

	void onUpdate(const float deltaTime) override;
public:
	PlayerController(Game& game, Entity& owner);
	
	~PlayerController();
};

