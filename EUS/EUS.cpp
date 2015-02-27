#include "EUS.h"
#include "MapBuilder.h"

EUS::EUS() : Game() {
}

#pragma region Protected members
void EUS::onExit() {

}

void EUS::onEvent(const SDL_Event& e) {

}

#include "ModelRenderer.h"

static Entity* box;
static Entity* map;
static Model* model;
static ModelRenderer* renderer;

void EUS::initialize() {
	texture = content().load<Texture>("tileset");
	
	MapBuilder b(*this);
	map = b.buildMap("test", "bordersheet", 32);
	
	model = content().load<Model>("tuksutin");

	box = new Entity();
	renderer = new ModelRenderer(*this, *box, model);
	renderer->enable();
	
	box->addComponent(renderer);
}

void EUS::update(float deltaTime) {
	map->update();
	map->childsForEach([](Entity* const e) { e->update();  });
}

static float r = 0.0f;

void EUS::draw(float deltaTime) {
	box->getTransform().setScale(0.5f);
	box->getTransform().setX(0.0f);
	box->getTransform().setY(3.0f);
	box->getTransform().setRotation(r, Vector3(0.0f, 0.0f, 1.0f));

	box->draw();

	r += 0.025f;

	std::cout << r << std::endl;
	//box->getTransform().setRotation(r, Vector3(1.0f, 1.0f, 1.0f));
	//box->getTransform().translate(Vector3(0.0025, 0.0025f, 0.0025f));

	/*sb.begin();

	//sb.draw(texture, pmath::Rectf(0, 0, 1280, 720));
	map->childsForEach([](Entity* const e) { e->draw();  });

	sb.end();*/
}

#pragma endregion Protected members

EUS::~EUS() {
}
