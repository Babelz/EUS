#include "UnitActionControl.h"

UnitActionControl::UnitActionControl(Game& game, Entity& owner) : DrawableComponent(game, owner), input(game.inputManager()) {
	entity = new Entity();
	
	Texture* wait = game.content().load<Texture>("wait");
	Texture* attack = game.content().load<Texture>("attack");

	waitRenderer = new ModelRenderer(game, *entity, game.content().load<Model>("box"));
	waitRenderer->setTextureId(wait->getId());
	waitRenderer->enable();

	attackRenderer = new ModelRenderer(game, *entity, game.content().load<Model>("box"));
	attackRenderer->setTextureId(attack->getId());
	attackRenderer->enable();

	entity->addComponent(waitRenderer);
	entity->addComponent(attackRenderer);

	selector = new Entity();
	
	selectorRenderer = new ModelRenderer(game, *selector, game.content().load<Model>("box"));
	selectorRenderer->setTextureId(game.content().load<Texture>("selector")->getId());
	selectorRenderer->enable();

	selector->addComponent(selectorRenderer);
}

#pragma region Protected members
void UnitActionControl::onDraw(const float deltaTime) {
	if (!drawAttackIndex) {
		entity->getTransform().setX(getGame().view().getX());
		entity->getTransform().setY(getGame().view().getY());
		entity->getTransform().setZ(2.0f);
		waitRenderer->draw(deltaTime);

		entity->getTransform().setY(getGame().view().getY() - 2.0f);
		attackRenderer->draw(deltaTime);

		entity->getTransform().setX(getGame().view().getX());
		entity->getTransform().setY(getGame().view().getY());
		entity->getTransform().setZ(2.0f);

		selector->getTransform().setX(entity->getTransform().getX() + 2.0f);
		selector->getTransform().setY(entity->getTransform().getY() + selectedIndex * -2.0f);
		selector->getTransform().setZ(2.0f);
		selectorRenderer->draw(deltaTime);
	} else {
		pmath::Vec2i attackVector = getAttackVector();

		selector->getTransform().setX(attackVector.x * 2.0f + 1.0f);
		selector->getTransform().setY(-attackVector.y * 2.0f);

		selectorRenderer->draw(deltaTime);
	}
}
#pragma endregion 

#pragma region Public members
void UnitActionControl::computeActions(MapGrid& grid, Entity& e, const std::string& otherPlayer) {
	selectedIndex = 0;
	buttonsCount = 0;
	attackIndex = 0;

	drawAttackIndex = false;

	attackPositions.clear();

	const int x = static_cast<int>(std::fabs(e.getTransform().getX()) / 2.0f);
	const int y = static_cast<int>(std::fabs(e.getTransform().getY()) / 2.0f);
	
	const int top = y - 1;
	const int bottom = y + 1;

	const int left = x - 1;
	const int right = x + 1;

	if (top >= 0 && x >= 0 && x < grid.getWidth()) {
		if (grid.nodeAtIndex(top, x).hasEntity() && grid.nodeAtIndex(top, x).getEntity()->isTagged(otherPlayer)) {
			attackPositions.push_back(pmath::Vec2i(x, top));
		}
	}
	if (bottom < grid.getHeight() && x >= 0 && x < grid.getWidth()) {
		if (grid.nodeAtIndex(bottom, x).hasEntity() && grid.nodeAtIndex(bottom, x).getEntity()->isTagged(otherPlayer)) {
			attackPositions.push_back(pmath::Vec2i(x, bottom));
		}
	}
	if (left >= 0 && y >= 0 && y < grid.getHeight()) {
		if (grid.nodeAtIndex(y, left).hasEntity() && grid.nodeAtIndex(y, left).getEntity()->isTagged(otherPlayer)) {
			attackPositions.push_back(pmath::Vec2i(left, y));
		}
	}
	if (right < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
		if (grid.nodeAtIndex(y, right).hasEntity() && grid.nodeAtIndex(y, right).getEntity()->isTagged(otherPlayer)) {
			attackPositions.push_back(pmath::Vec2i(right, y));
		}
	}

	if (attackPositions.size() > 0) attackRenderer->show();
	else                            attackRenderer->hide();

	selectedRenderer = waitRenderer;
	buttonsCount = attackPositions.size() > 0 ? 1 : 0;
	selectedIndex = 0;
}
void UnitActionControl::setAttackCallback(Callback callback) {
	this->attack = callback;
}
void UnitActionControl::setCancelCallback(Callback callback) {
	this->cancel = callback;
}
void UnitActionControl::setMoveCallback(Callback callback) {
	this->move = callback;
}
void UnitActionControl::bindInput() {
	input.bind("next_btn", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		selectedIndex++;

		if (selectedIndex > buttonsCount) selectedIndex = buttonsCount;
	}, 1, new KeyTrigger(SDLK_s));

	input.bind("prev_btn", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		selectedIndex--;

		if (selectedIndex < 0) selectedIndex = 0;
	}, 1, new KeyTrigger(SDLK_w));
	
	input.bind("select_btn", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		if (selectedIndex == 0) move();
		else if (selectedIndex == 1) selectAttackIndex();
	}, 1, new KeyTrigger(SDLK_e));

	input.bind("close", [this](InputArgs args) {
		if (args.state != PRESSED) return;
		
		cancel();
	}, 1, new KeyTrigger(SDLK_q));
}
void UnitActionControl::unbindInput() {
	input.unbind("next_btn");
	input.unbind("prev_btn");
	input.unbind("select_btn");
	input.unbind("close");

	if (drawAttackIndex) {
		input.unbind("next_index");
		input.unbind("prev_index");
		input.unbind("select_index");
		input.unbind("close_selection");
	}
}
void UnitActionControl::selectAttackIndex() {
	unbindInput();

	drawAttackIndex = true;

	input.bind("next_index", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		attackIndex++;

		if (attackIndex >= attackPositions.size()) attackIndex = attackPositions.size() - 1;
	}, 1, new KeyTrigger(SDLK_w));

	input.bind("prev_index", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		attackIndex--;

		if (attackIndex < 0) attackIndex = 0;
	}, 1, new KeyTrigger(SDLK_s));
	
	input.bind("select_index", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		attack();
	}, 1, new KeyTrigger(SDLK_e));

	input.bind("close_selection", [this](InputArgs args) {
		if (args.state != PRESSED) return;

		cancel();
	}, 1, new KeyTrigger(SDLK_q));
}
pmath::Vec2i UnitActionControl::getAttackVector() {
	return attackPositions[attackIndex];
}
#pragma endregion

UnitActionControl::~UnitActionControl() {
	delete entity;
	delete selector;
}
