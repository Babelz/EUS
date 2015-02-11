#pragma once
#include "Sprite.h"
#include "Entity.h"
#include "Game.h"

class SpriteRenderer : public DrawableComponent {
private:
	Sprite& m_sprite;
	Game& game;

	bool follow;
public:
	SpriteRenderer(Game& game, Entity& owner, Sprite& sprite);

	Sprite& sprite();
	void changeSprite(Sprite& sprite);

	void beginFollowing();
	void stopFollowing();

	void update();
	void draw();

	~SpriteRenderer();
};

