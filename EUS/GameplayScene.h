#pragma once
#include "SceneManager.h"

class GameplayScene : public Scene {
protected:
	void onActivate();
public:
	GameplayScene(const std::string& name);

	void update(const float deltaTime);
	void draw(const float deltaTime);

	~GameplayScene();
};

