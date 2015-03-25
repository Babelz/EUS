#include "PlayerCursor.h"

PlayerCursor::PlayerCursor(Game& game, Entity& owner) : Component(game, owner),
														animator(nullptr) {
}

#pragma region Protected members
void PlayerCursor::onDestroyed() {
	animator->destroy();
}

void PlayerCursor::onInitialize() {
	Texture* sheet = getGame().content().load<Texture>("cursor");
	
	animator = new SpriteAnimator(getGame(), getOwner());
	animator->enable();

	const std::string name = "loop";

	animator->setTexture(sheet);
	animator->createAnimation(name, 0, 0);
	animator->setAnimationDuration(name, 0.05f);
	animator->setAnimationFramesCount(name, 8);
	animator->setAnimatorSize(pmath::Vec2f(64.0f));
	animator->setFrameSize(32);
	animator->changeAnimation(name);

	getOwner().addComponent(animator);
}
#pragma endregion

#pragma region Public members
void PlayerCursor::hide() {
	assert(animator != nullptr);

	animator->hide();
}
void PlayerCursor::show() {
	assert(animator != nullptr);

	animator->show();
}
#pragma endregion

PlayerCursor::~PlayerCursor() {
}
