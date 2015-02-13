#pragma once
#include "Sprite.h"
#include "Entity.h"
#include "Game.h"

class SpriteRenderer : public DrawableComponent {
private:
	Sprite& sprite;
	Game& game;

	bool follow;
public:
	SpriteRenderer(Game& game, Entity& owner, Sprite& sprite);

	Sprite& getSprite();
	void setSprite(Sprite& sprite);

	void beginFollowing();
	void stopFollowing();

	void update();
	void draw();

	~SpriteRenderer();
};

