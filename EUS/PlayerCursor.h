#pragma once
#include "Entity.h"

// Class for controlling units and interactions.
class PlayerCursor : public DrawableComponent {
private:

protected:
	void onInitialize() override;

	void onUpdate(const float deltaTime) override;
	void onDraw(const float deltaTime) override;
public:
	PlayerCursor(Game& game, Entity& owner);

	~PlayerCursor();
};

