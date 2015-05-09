#pragma once
#include "Entity.h"
#include "ModelRenderer.h"
#include "DijkstraPathfinder.h"

class MovementSpaceHandler : public DrawableComponent {
private:
	DijkstraPathfinder* pathfinder;

	// Selected unit.
	Entity* unit;
	// Entity that owns the renderer.
	Entity* area;
	// Renderer used to render the area.
	ModelRenderer* renderer;
	MapGrid& grid;

	std::vector<DijkstarNode> nodes;
protected:
	void onDraw(const float deltaTime) override;
public:
	MovementSpaceHandler(Game& game, Entity& owner, MapGrid& grid);

	// Unit to select, row and column index of the unit in the map grid. 
	void changeSelectedUnit(Entity* unit);

	const bool hasUnitSelected() const;
	const bool canMoveTo(const int x, const int y) const;

	Entity* getSelectedUnit();

	const int getSelectedX() const;
	const int getSelectedY() const;

	void generatePointMapTo(std::vector<pmath::Vec2f>& outMap, const int x, const int y) const;

	~MovementSpaceHandler() override;
};

