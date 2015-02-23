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
	
	model = content().load<Model>("box");

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
	for (size_t i = 1; i < 10; i++) {
		for (size_t j = 1; j < 10; j++) {
			box->getTransform().setX(j + ((j - 1) * 1.0f));
			box->getTransform().setY(i + ((i - 1) * 1.0f));

			if (j % 2 == 0) 
				box->getTransform().setRotation(r, Vector3(0.0f, 1.0f, 0.0f));
			else
				box->getTransform().setRotation(-r, Vector3(0.0f, 1.0f, 0.0f));
				
			box->draw();
		}
	}
	//box->getTransform().setRotation(r, Vector3(1.0f, 0.0f, 0.0f));

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
