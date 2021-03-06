#include "EUS.h"
#include "GameplayScene.h"

EUS::EUS() : Game() {
}

#pragma region Protected members
void EUS::onExit() { }

void EUS::onEvent(const SDL_Event& e) { 
}

static Entity* p;

void EUS::initialize() {
	// Change scene.
	sceneManager().addScene(new GameplayScene());
	sceneManager().changeScene("gameplay");
}

void EUS::update(const float deltaTime) {
	sceneManager().update(deltaTime);
}

void EUS::draw(const float deltaTime) {
	sceneManager().draw(deltaTime);
}

#pragma endregion Protected members

EUS::~EUS() {
}
