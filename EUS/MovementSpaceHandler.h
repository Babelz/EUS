#pragma once
#include "Entity.h"
#include "ModelRenderer.h"

class MovementSpaceHandler : public DrawableComponent {
private:
	const int mapWidth;
	const int mapHeight;

	// Selected unit.
	Entity* unit;
	// Renderer used to render the area.
	ModelRenderer* renderer;

	int x;
	int y;
	int width;
	int height;

protected:
	void onDraw(const float deltaTime) override;
public:
	MovementSpaceHandler(Game& game, Entity& owner, int mapWidth, int mapHeight);

	void changeSelectedUnit(Entity* unit);
	const bool hasUnitSelected() const;

	~MovementSpaceHandler();
};

