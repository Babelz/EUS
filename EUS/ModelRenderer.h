#pragma once
#include "DrawableComponent.h"
#include "Resources.h"
#include "Game.h"
#include <algorithm>

class ModelRenderer : public DrawableComponent {
private:
	Model* model;
	Effect* shader;

	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint indexBuffer;

	void releaseBuffers();
	void initializeBuffers();
protected:
	void onDraw();
public:
	ModelRenderer(Game& game, Entity& owner, Model* const model, const int updateOrder = 0, const int drawOrder = 0);
	ModelRenderer(Game& game, Entity& owner, const int updateOrder = 0, const int drawOrder = 0);

	Model& getModel();
	void setModel(Model* const model);

	~ModelRenderer();
};

