#include "EUS.h"

EUS::EUS() {
}

#pragma region Protected members
void EUS::onExit() {

}

void EUS::onEvent(const SDL_Event& e) {

}

void EUS::initialize() {
	texture = content().load<Texture>("tileset");
}
void EUS::update(float deltaTime) {

}

static float pos = 0.0f;

void EUS::draw(float deltaTime) {
	pos += 25.2323f * deltaTime;
	
	spriteBatch().begin();

	spriteBatch().draw(texture, pmath::Rectf(pos, 0, 64, 64), pmath::Rectf(100, 100, 256, 256), pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
