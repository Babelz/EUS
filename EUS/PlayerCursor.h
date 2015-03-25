#pragma once
#include "Entity.h"
#include "SpriteAnimator.h"

// Class for controlling units and interactions.
class PlayerCursor : public Component {
private:
	SpriteAnimator* animator;
protected:
	void onInitialize() override;

	virtual void onDestroyed() override;
public:
	PlayerCursor(Game& game, Entity& owner);

	void hide();
	void show();

	~PlayerCursor();
};

