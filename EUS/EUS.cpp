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

static Entity* map;
static Model* model;
static ModelRenderer* renderer;

void EUS::initialize() {
	texture = content().load<Texture>("tileset");
	
	MapBuilder b(*this);
	map = b.buildMap("test", "bordersheet", 32);
	
	model = content().load<Model>("box");

	Entity* e = new Entity();
	renderer = new ModelRenderer(*this, *e, model);
	renderer->enable();
}

void EUS::update(float deltaTime) {
	map->update();
	map->childsForEach([](Entity* const e) { e->update();  });
}
void EUS::draw(float deltaTime) {
	renderer->draw();
	/*sb.begin();

	//sb.draw(texture, pmath::Rectf(0, 0, 1280, 720));
	map->childsForEach([](Entity* const e) { e->draw();  });

	sb.end();*/
}

#pragma endregion Protected members

EUS::~EUS() {
}
