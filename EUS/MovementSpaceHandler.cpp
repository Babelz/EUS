#include "MovementSpaceHandler.h"


MovementSpaceHandler::MovementSpaceHandler(Game& game, Entity& owner, int mapWidth, int mapHeight) : DrawableComponent(game, owner),
																									 mapWidth(mapWidth),
																									 mapHeight(mapHeight),
																									 unit(nullptr) {
	// Initialize renderer.
	Model* model = game.content().load<Model>("box");
	model->setTexture(game.content().load<Texture>("selected"));

	// Owner owns the renderer, but its draw calls are delegated to this component.
	renderer = new ModelRenderer(game, owner, model);
	renderer->enable();
}

#pragma region Protected members
void MovementSpaceHandler::onDraw(const float deltaTime) {
	if (!hasUnitSelected()) return;

	// TODO: draw the selected area.
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {

		}
	}
}
#pragma endregion

#pragma region Public member
void MovementSpaceHandler::changeSelectedUnit(Entity* unit) {
	
}
const bool MovementSpaceHandler::hasUnitSelected() const {
}
#pragma endregion


MovementSpaceHandler::~MovementSpaceHandler() {
}
