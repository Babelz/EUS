#include "PlayerCursor.h"
#include "ModelRenderer.h"

PlayerCursor::PlayerCursor(Game& game, Entity& owner) : Component(game, owner),
														animator(nullptr) {
}

#pragma region Protected members
void PlayerCursor::onDestroyed() {
	//animator->destroy();
}

void PlayerCursor::onInitialize() {
	/*Texture* sheet = getGame().content().load<Texture>("cursor");
	
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

	getOwner().addComponent(animator);*/

	Model* model = getGame().content().load<Model>("box");
	model->setTexture(getGame().content().load<Texture>("cursor1"));

	ModelRenderer* renderer = new ModelRenderer(getGame(), getOwner(), model);
	renderer->setTextureId(model->getTexture()->getId());
	renderer->enable();

	getOwner().getTransform().setX(0.0f);
	getOwner().getTransform().setY(0.0f);
	getOwner().getTransform().setZ(0.25f);

	getOwner().addComponent(renderer);
}
#pragma endregion

#pragma region Public members
void PlayerCursor::hide() {
	getOwner().getComponent<ModelRenderer>()->hide();
}
void PlayerCursor::show() {
	getOwner().getComponent<ModelRenderer>()->show();
}
#pragma endregion

PlayerCursor::~PlayerCursor() {
}
