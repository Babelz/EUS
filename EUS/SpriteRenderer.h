#pragma once
#include "Sprite.h"
#include "Entity.h"
#include "Game.h"

class SpriteRenderer : public DrawableComponent {
private:
	std::shared_ptr<Sprite> sprite;
	Game& game;

	bool follow;
protected:
	void onUpdate();
	void onDraw();
public:
	SpriteRenderer(Game& game, Entity& owner, Sprite* const sprite);
	SpriteRenderer(Game& game, Entity& owner);

	Sprite& getSprite();
	void setSprite(Sprite* const sprite);

	void beginFollowing();
	void stopFollowing();

	~SpriteRenderer();
};

