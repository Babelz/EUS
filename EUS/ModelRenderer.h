#pragma once
#include "DrawableComponent.h"
#include "Resources.h"
#include "Game.h"
#include "GLM.h"
#include <algorithm>

class ModelRenderer : public DrawableComponent {
private:
	Model* model;
	Effect* shader;

	GLuint vertexArray;
	GLuint vertexBuffer;

	void releaseBuffers();
	void initializeBuffers();
protected:
	void onInitialize();
	void onDraw(const float deltaTime);
public:
	ModelRenderer(Game& game, Entity& owner, Model* const model, const int updateOrder = 0, const int drawOrder = 0);

	~ModelRenderer();
};

