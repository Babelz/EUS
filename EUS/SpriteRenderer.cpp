#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Game& game, Entity& owner, Sprite* sprite) : DrawableComponent(game, owner),
																			sprite(sprite),
																			follow(true) {
}
SpriteRenderer::SpriteRenderer(Game& game, Entity& owner) : DrawableComponent(game, owner),
															sprite(nullptr),
															follow(true) {

}

#pragma region Protected members
void SpriteRenderer::onUpdate(const float deltaTime) {
	if (sprite == nullptr) return;

	if (follow) {
		sprite->setX(getOwner().getTransform().getPosition().x);
		sprite->setY(getOwner().getTransform().getPosition().y);
	}
}
void SpriteRenderer::onDraw(const float deltaTime) {
	if (sprite == nullptr) return;

	sprite->draw(getGame().spriteBatch());
}
#pragma endregion

#pragma region Public members
Sprite& SpriteRenderer::getSprite() {
	return *sprite;
}
void SpriteRenderer::setSprite(Sprite* const sprite) {
	this->sprite = sprite;
}

void SpriteRenderer::beginFollowing() {
	follow = true;
}
void SpriteRenderer::stopFollowing() {
	follow = false;
}
#pragma endregion

SpriteRenderer::~SpriteRenderer() {
	delete sprite;
}
