#include "EUSEntityBuilder.h"
#include "PlayerController.h"
#include "ModelRenderer.h"
#include "UnitInformation.h"
#include "AStarPathfinder.h"
#include "PointNavigator.h"
#include "UnitActionControl.h"

EUSEntityBuilder::EUSEntityBuilder(const std::string& name, Game& game) : EntityBuilder(name, game) {
}

#pragma region Public members
Entity* EUSEntityBuilder::buildPlayer(const std::string& name) const {
	Entity* player = new Entity();
	player->getTransform().setPosition(Vector3(256.0f, 256.0f, 0.0f));
	player->tag(name);

	PlayerCursor* cursor = new PlayerCursor(game(), *player);
	cursor->enable();

	player->addComponent(cursor);

	PlayerController* controller = new PlayerController(game(), *player, name);
	controller->enable();

	player->addComponent(controller);

	UnitActionControl* unitActionControl = new UnitActionControl(game(), *player);
	unitActionControl->enable();
	unitActionControl->hide();

	player->addComponent(unitActionControl);

	return player;
}
Entity* EUSEntityBuilder::buildRifleman(const std::string& ownerTag) const {
	const static std::string PLAYER1 = std::string("p1");
	const static std::string PLAYER2 = std::string("p2");

	assert(ownerTag == PLAYER1 || ownerTag == PLAYER2);

	Entity* rifleman = new Entity();
	rifleman->tag(ownerTag);
	rifleman->tag("unit");

	std::string textureName = ownerTag + "inf";

	Texture* texture = game().content().load<Texture>(textureName);
	Model* model = game().content().load<Model>("box");
	model->setTexture(texture);

	ModelRenderer* renderer = new ModelRenderer(game(), *rifleman, model);
	renderer->enable();

	PointNavigator* navigator = new PointNavigator(game(), *rifleman);
	navigator->enable();

	// Initialize unit information.
	const static std::list<NodeInfo> walkableTerrainTypes =
	{
		NodeInfo(true, TileType::Plains, 1)
	};
	
	const static DamageType damageType = DamageType::LightWeight;
	const static ArmorType armorType = ArmorType::Light;
	const static OrganicUnit organicUnit = OrganicUnit::GroundForces;
	
	const static int movementRange = 2;

	UnitInformation* unitInformation = new UnitInformation(game(), *rifleman,
														   walkableTerrainTypes,
														   damageType,
														   armorType,
														   organicUnit,
														   movementRange);

	rifleman->addComponent(renderer);
	rifleman->addComponent(unitInformation);
	rifleman->addComponent(navigator);

	

	return rifleman;
}
#pragma endregion

EUSEntityBuilder::~EUSEntityBuilder() {
}
