#include "EUS.h"
#include "GameplayScene.h"

EUS::EUS() : Game() {
}

#pragma region Protected members
void EUS::onExit() { }

void EUS::onEvent(const SDL_Event& e) { 
}

void EUS::initialize() {
	sceneManager().addScene(new GameplayScene());
	sceneManager().changeScene("gameplay");
	
	inputManager().bind("move l", [this](InputArgs& args) {
		view().setX(view().getX() - 0.05f);
	}, 1, new KeyTrigger(SDLK_a));

	inputManager().bind("move r", [this](InputArgs& args) {
		view().setX(view().getX() + 0.05f);
	}, 1, new KeyTrigger(SDLK_d));

	inputManager().bind("move u", [this](InputArgs& args) {
		view().setY(view().getY() + 0.05f);
	}, 1, new KeyTrigger(SDLK_w));

	inputManager().bind("move d", [this](InputArgs& args) {
		view().setY(view().getY() - 0.05f);
	}, 1, new KeyTrigger(SDLK_s));


	inputManager().bind("rot x+", [this](InputArgs& args) {
		view().setRotX(view().getRotX() + 0.05f);
	}, 1, new KeyTrigger(SDLK_r));

	inputManager().bind("rot x-", [this](InputArgs& args) {
		view().setRotX(view().getRotX() - 0.05f);
	}, 1, new KeyTrigger(SDLK_t));


	inputManager().bind("rot y+", [this](InputArgs& args) {
		view().setRotY(view().getRotY() + 0.05f);
	}, 1, new KeyTrigger(SDLK_e));

	inputManager().bind("rot y-", [this](InputArgs& args) {
		view().setRotY(view().getRotY() - 0.05f);
	}, 1, new KeyTrigger(SDLK_q));


	inputManager().bind("res", [this](InputArgs& args) {
		view().setRotY(0.0f);
		view().setRotX(0.0f);
	}, 1, new KeyTrigger(SDLK_F1));
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
