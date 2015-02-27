#pragma once
#include "Sprite.h"
#include "Entity.h"
#include "Game.h"

class SpriteRenderer : public DrawableComponent {
private:
	Sprite* sprite;
	
	bool follow;
protected:
	void onUpdate(const float deltaTime);
	void onDraw(const float deltaTime);
public:
	SpriteRenderer(Game& game, Entity& owner, Sprite* const sprite);
	SpriteRenderer(Game& game, Entity& owner);

	Sprite& getSprite();
	void setSprite(Sprite* const sprite);

	void beginFollowing();
	void stopFollowing();

	~SpriteRenderer();
};

