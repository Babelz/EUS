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
	for (int i = 1; i < (1920 * 1200 + 1) * 8 * 8; i++)
	{
		saatanat[i - 1] = i;
	}
	texture = content().load<Texture>("tileset");
}
void EUS::update(float deltaTime) {

}

static float pos = 0.0f;

void EUS::draw(float deltaTime) {
	pos += 10.2323f * deltaTime;
	
	spriteBatch().begin();
	
	for (int i = 0; i < 1200 / 32; i++)
	{
		for (int j = 0; j < 1920 / 32; j++)
		{
			spriteBatch().draw(texture, pmath::Rectf(pos * saatanat[i * j], 0, 200, 200), pmath::Rectf(j * 32, i * 32, 32, 32), pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	spriteBatch().end();
}

#pragma endregion Protected members

EUS::~EUS() {
}
