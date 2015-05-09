#pragma once
#include "Entity.h"
#include "ModelRenderer.h"
#include "DijkstraPathfinder.h"

class MovementSpaceHandler : public DrawableComponent {
private:
	DijkstraPathfinder* pathfinder;

	const int mapWidth;
	const int mapHeight;

	// Selected unit.
	Entity* unit;
	// Entity that owns the renderer.
	Entity* area;
	// Renderer used to render the area.
	ModelRenderer* renderer;
	MapGrid& grid;

	std::vector<DijkstarNode> nodes;

	int x;
	int y;
protected:
	void onDraw(const float deltaTime) override;
public:
	MovementSpaceHandler(Game& game, Entity& owner, const int mapWidth, const int mapHeight, MapGrid& grid);

	void changeSelectedUnit(Entity* unit);
	const bool hasUnitSelected() const;

	~MovementSpaceHandler() override;
};

