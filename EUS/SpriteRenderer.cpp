#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Game& game, Entity& owner, Sprite& sprite) : DrawableComponent(owner),
																			game(game),
																			sprite(sprite),
																			follow(false) {
}

#pragma region Public members
Sprite& SpriteRenderer::getSprite() {
	return sprite;
}
void SpriteRenderer::setSprite(Sprite& sprite) {
	sprite = sprite;
}

void SpriteRenderer::beginFollowing() {
	follow = true;
}
void SpriteRenderer::stopFollowing() {
	follow = false;
}

void SpriteRenderer::update() {
	if (follow) {
		sprite.setX(getOwner().getX());
		sprite.setY(getOwner().getY());
	}
}
void SpriteRenderer::draw() {
	sprite.draw(game.spriteBatch());
}
#pragma endregion

SpriteRenderer::~SpriteRenderer() {
}
