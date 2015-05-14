#pragma once
#include "Entity.h"
#include "PlayerCursor.h"

class PlayerController : public Component {
private:
	std::string name;
	Entity* selectedUnit;
	PlayerCursor* cursor;
	
	float bottomBound;
	float rightBound;

	bool inBounds(const float nextX, const float nextY);
	void interact();
protected:
	void onDestroyed() override;

	void onInitialize() override;

	void onUpdate(const float deltaTime) override;
public:
	PlayerController(Game& game, Entity& owner, const std::string& name);
	
	void bindInput();
	void unbindInput();

	~PlayerController();
};

