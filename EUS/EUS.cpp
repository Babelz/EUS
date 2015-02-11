#include "EUS.h"

EUS::EUS() {
}

#pragma region Protected members
void EUS::onExit() {

}

void EUS::onEvent(const SDL_Event& e) {

}

void EUS::initialize() {
	sprite.swapTexture(content().load<Texture>("pidginz"));
	sprite.setScale(0.05f);
}
void EUS::update(float deltaTime) {

}

static float asd = 0.0f;

void EUS::draw(float deltaTime) {

	asd += 0.82323f;

	pmath::Vec2f size(asd - sprite.textureWidth() * 0.05f * deltaTime,
					  asd - sprite.textureHeight() * 0.05f * deltaTime);

	spriteBatch().begin();

	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 60; j++) {
			sprite.setX(j * size.x);
			sprite.setY(i * size.y);

			sprite.draw(spriteBatch());
		}
	}

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
