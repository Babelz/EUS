#pragma once
#include "SceneManager.h"
#include "MapBuilder.h"

class GameplayScene : public Scene {
protected:
	void onActivate();
public:
	GameplayScene();

	void update(const float deltaTime);
	void draw(const float deltaTime);

	~GameplayScene();
};
