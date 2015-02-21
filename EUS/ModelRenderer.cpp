#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(Entity& owner, Model* const model, const int updateOrder, const int drawOrder) : DrawableComponent(owner, updateOrder, drawOrder),
																										      model(model) {
}
ModelRenderer::ModelRenderer(Entity& owner, const int updateOrder, const int drawOrder) : ModelRenderer(owner, nullptr, updateOrder, drawOrder) {
}


#pragma region Protected members
void ModelRenderer::onDraw() {
	if (model != nullptr && !model->empty()) {
		// TODO: draw the model.
	}
}
#pragma endregion


#pragma region Public members
Model& ModelRenderer::getModel() {
	return *model;
}
void ModelRenderer::setModel(Model* const model) {
	this->model = model;
}
#pragma endregion

ModelRenderer::~ModelRenderer() {
}
