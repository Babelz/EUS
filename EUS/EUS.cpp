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
	sprite.setScale(0.15f);
}
void EUS::update() {

}

static float asd = 0.0f;

void EUS::draw() {

	asd += 0.42323f;

	pmath::Vec2f size(asd - sprite.textureWidth() * 0.15f,
					  asd - sprite.textureHeight() * 0.15f);

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
