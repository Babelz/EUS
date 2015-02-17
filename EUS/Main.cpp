#include "EUS.h"
#include "EntityBuilder.h"
#include "SheetMapping.h"
#include "NamedTileSheet.h"

void bTests(Game& g);

int main(int argc, char** argv) {
	SheetMapping m;

	m.load("Content\\test.txt");

	NamedTileSheet s(nullptr, 32);

	s.load("Content\\test.txt");

	EUS game;

	bTests(game);

	game.run();

	return 0;
}

void bTests(Game& g) {
	/*EntityBuilder b;

	b.borderMap(g);*/
}
