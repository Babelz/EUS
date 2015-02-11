#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Game& game, Entity& owner, Sprite& sprite) : DrawableComponent(owner),
																			game(game),
																			m_sprite(sprite),
																			follow(false) {
}

#pragma region Public members
Sprite& SpriteRenderer::sprite() {
	return m_sprite;
}
void SpriteRenderer::changeSprite(Sprite& sprite) {
	m_sprite = sprite;
}

void SpriteRenderer::beginFollowing() {
	follow = true;
}
void SpriteRenderer::stopFollowing() {
	follow = false;
}

void SpriteRenderer::update() {
	if (follow) {
		m_sprite.setX(getOwner().getX());
		m_sprite.setY(getOwner().getY());
	}
}
void SpriteRenderer::draw() {
	m_sprite.draw(game.spriteBatch());
}
#pragma endregion

SpriteRenderer::~SpriteRenderer() {
}
