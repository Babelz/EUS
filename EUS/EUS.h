#pragma once
#include <list>
#include "Game.h"
#include "Sprite.h"
#include "Resources.h"

class EUS : public Game {
private:
	Sprite sprite;
protected:
	virtual void onExit();

	virtual void onEvent(const SDL_Event& e);

	virtual void initialize();
	virtual void update();
	virtual void draw();
public:
	EUS();

	~EUS();
};

