#pragma once
#include "Scene.h"

class SceneComponent {
	virtual void onUpdate(const float deltaTime);
public:
	SceneComponent(S);

	void enable();
	void disable();

	void update(const float deltaTime);

	~SceneComponent();
};

