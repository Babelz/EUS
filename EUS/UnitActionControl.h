#pragma once
#include "Entity.h"
#include "ModelRenderer.h"
#include "MapGrid.h"

enum Action {
	Wait,
	Attack
};

typedef std::function<void()> Callback;

class UnitActionControl : public DrawableComponent {
private:
	Entity* entity;
	Entity* selector;

	InputManager& input;

	ModelRenderer* backgroundRenderer;
	ModelRenderer* waitRenderer;
	ModelRenderer* attackRenderer;
	ModelRenderer* selectedRenderer;
	ModelRenderer* selectorRenderer;
	
	std::vector<pmath::Vec2i> attackPositions;

	Callback cancel;
	Callback attack;
	Callback move;

	int selectedIndex;
	int buttonsCount;

	bool drawAttackIndex;

	int attackIndex;

	void selectAttackIndex();
protected:
	void onDraw(const float deltaTime) override;
public:
	UnitActionControl(Game& game, Entity& owner);

	void selectNext();
	void selectPrevious();
	void computeActions(MapGrid& grid, Entity& e, const std::string& otherPlayer);

	void setAttackCallback(Callback callback);
	void setCancelCallback(Callback callback);
	void setMoveCallback(Callback callback);

	void bindInput();
	void unbindInput();
	pmath::Vec2i getAttackVector();

	~UnitActionControl();
};

