#pragma once
#include <list>
#include "Game.h"
#include "Sprite.h"
#include "Resources.h"

class EUS : public Game {
private:
	Texture* texture;
protected:
	virtual void onExit();

	virtual void onEvent(const SDL_Event& e);

	void initialize();
	void update(float deltaTime);
	void draw(float deltaTime);
public:
	EUS();

	~EUS();
};

