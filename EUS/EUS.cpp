#include "EUS.h"

EUS::EUS() {
}

#pragma region Protected members
void EUS::onExit() {

}

void EUS::onEvent(const SDL_Event& e) {

}


static float saatanat[1920 * 1200 * 8 * 8];

void EUS::initialize() {
	texture = content().load<Texture>("tileset");
}

void EUS::update(float deltaTime) {
}
void EUS::draw(float deltaTime) {
	spriteBatch().begin();

	spriteBatch().draw(texture, pmath::Rectf(0, 0, 1280, 720));

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
