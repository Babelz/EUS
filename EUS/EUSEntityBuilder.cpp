#include "EUSEntityBuilder.h"
#include "PlayerController.h"
#include "ModelRenderer.h"

EUSEntityBuilder::EUSEntityBuilder(const std::string& name, Game& game) : EntityBuilder(name, game) {
}

#pragma region Public members
Entity* EUSEntityBuilder::buildPlayer() const {
	Entity* player = new Entity();
	player->getTransform().setPosition(Vector3(256.0f, 256.0f, 0.0f));

	PlayerCursor* cursor = new PlayerCursor(game(), *player);
	cursor->enable();

	player->addComponent(cursor);

	PlayerController* controller = new PlayerController(game(), *player);
	controller->enable();

	player->addComponent(controller);

	return player;
}
Entity* EUSEntityBuilder::buildRifleman(const std::string& ownerTag) const {
	const static std::string CPU = std::string("cpu");
	const static std::string PLAYER = std::string("player");

	assert(ownerTag == CPU || ownerTag == PLAYER);

	Entity* rifleman = new Entity();
	rifleman->tag(ownerTag);
	rifleman->tag("unit");

	std::string textureName;

	if (ownerTag == PLAYER) {
		// Player init.
		textureName = "p1inf";
	} else {
		// CPU init.
		textureName = "p2inf";
	}

	Texture* texture = game().content().load<Texture>(textureName);
	Model* model = game().content().load<Model>("box");
	model->setTexture(texture);

	ModelRenderer* renderer = new ModelRenderer(game(), *rifleman, model);
	renderer->enable();

	rifleman->addComponent(renderer);

	return rifleman;
}
#pragma endregion

EUSEntityBuilder::~EUSEntityBuilder() {
}
