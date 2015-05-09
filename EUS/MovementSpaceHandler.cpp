#include "MovementSpaceHandler.h"
#include "UnitInformation.h"
#include "MapGrid.h"

MovementSpaceHandler::MovementSpaceHandler(Game& game, Entity& owner, MapGrid& grid) : DrawableComponent(game, owner),
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

	UnitInformation* information = unit->getComponent<UnitInformation>();

	pathfinder->findPath(nodes, information->getTerrainInfos(), getSelectedX(), getSelectedY(), information->getMovementRange());
}

const bool MovementSpaceHandler::hasUnitSelected() const {
	return unit != nullptr;
}
const bool MovementSpaceHandler::canMoveTo(const int x, const int y) const {
	assert(hasUnitSelected());

	if (x == getSelectedX() && y == getSelectedY()) return false;

	for (DijkstarNode n : nodes) if (n.x == x && n.y == y) return true;

	return false;
}

Entity* MovementSpaceHandler::getSelectedUnit() {
	return unit;
}

const int MovementSpaceHandler::getSelectedX() const {
	return static_cast<int>(unit->getTransform().getX()) / 2;
}
const int MovementSpaceHandler::getSelectedY() const {
	return static_cast<int>(std::fabs(unit->getTransform().getY())) / 2;
}

void MovementSpaceHandler::generatePointMapTo(std::vector<pmath::Vec2f>& outMap, const int x, const int y) const {
	DijkstarNode current;

	for (DijkstarNode n : nodes) {
		if (n.x == x && n.y == y) {
			current = n;

			break;
		}
	}

	while (current.parentIndex != -1) {
		outMap.push_back(pmath::Vec2f(static_cast<float>(current.x * 2), 
									  static_cast<float>(-current.y * 2)));

		current = nodes[current.parentIndex];
	}

	std::reverse(outMap.begin(), outMap.end());
}
#pragma endregion


MovementSpaceHandler::~MovementSpaceHandler() {
	area->destroy();
}
