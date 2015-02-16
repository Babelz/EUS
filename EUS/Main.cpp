#include "EUS.h"
#include "EntityBuilder.h"

void bTests(Game& g);

int main(int argc, char** argv) {
	EUS game;

	bTests(game);

	game.run();

	return 0;
}

void bTests(Game& g) {
	EntityBuilder b;

	b.borderMap(g);
}
