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
	sprite.setScale(0.25f);
}
void EUS::update() {

}
void EUS::draw() {
	spriteBatch().begin();

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			sprite.setX(j * 128.0f);
			sprite.setY(i * 128.0f);

			sprite.draw(spriteBatch());
		}
	}

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
