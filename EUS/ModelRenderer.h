#pragma once
#include "DrawableComponent.h"
#include "Resources.h"

class ModelRenderer : public DrawableComponent {
private:
	Model* model;
protected:
	void onDraw();
public:
	ModelRenderer(Entity& owner, Model* const model, const int updateOrder = 0, const int drawOrder = 0);
	ModelRenderer(Entity& owner, const int updateOrder = 0, const int drawOrder = 0);

	Model& getModel();
	void setModel(Model* const model);

	void draw();

	~ModelRenderer();
};

