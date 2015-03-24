#pragma once
#include "Entity.h"
#include "PlayerCursor.h"

class PlayerController : public Component {
private:
	PlayerCursor* cursor;
protected:
	void onDestroyed() override;

	void onInitialize() override;

	void onUpdate(const float deltaTime) override;
public:
	PlayerController(Game& game, Entity& owner);
	
	~PlayerController();
};

