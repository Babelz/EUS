#include "MovementSpaceHandler.h"
#include "UnitInformation.h"
#include "MapGrid.h"

MovementSpaceHandler::MovementSpaceHandler(Game& game, Entity& owner, const int mapWidth, const int mapHeight, MapGrid& grid) : DrawableComponent(game, owner),
																																mapWidth(mapWidth),
																																mapHeight(mapHeight),
																																unit(nullptr),
																																grid(grid) {
	// Initialize area.
	area = new Entity();
	area->getTransform().setZ(owner.getTransform().getZ() - 0.1f);

	// Initialize renderer.
	Model* model = game.content().load<Model>("box");
	model->setTexture(game.content().load<Texture>("pidginz"));

	renderer = new ModelRenderer(game, *area, model);
	renderer->enable();

	pathfinder = new DijkstraPathfinder(game, owner, grid);
	pathfinder->enable();

	area->addComponent(pathfinder);
	area->addComponent(renderer);
}

#pragma region Protected members
void MovementSpaceHandler::onDraw(const float deltaTime) {
	if (!hasUnitSelected()) return;

	for (DijkstarNode n : nodes) {
		area->getTransform().setX(n.x * 2.0f);
		area->getTransform().setY(-n.y * 2.0f);
		
		renderer->draw(deltaTime);
	}
}
#pragma endregion

#pragma region Public member
void MovementSpaceHandler::changeSelectedUnit(Entity* unit) {
	this->unit = unit;

	nodes.clear();

	// Reset.
	if (unit == nullptr) {	
		return;
	}

	const int x = static_cast<int>(unit->getTransform().getX()) / 2;
	const int y = std::abs(static_cast<int>(unit->getTransform().getY())) / 2;

	UnitInformation* information = unit->getComponent<UnitInformation>();

	pathfinder->findPath(nodes, information->getTerrainInfos(), x, y, information->getMovementRange());
}
const bool MovementSpaceHandler::hasUnitSelected() const {
	return unit != nullptr;
}
#pragma endregion


MovementSpaceHandler::~MovementSpaceHandler() {
	area->destroy();
}
