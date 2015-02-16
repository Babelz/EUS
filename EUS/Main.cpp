#include "EUS.h"
#include "EntityBuilder.h"

void bTests();

int main(int argc, char** argv) {
	int* i = nullptr;
	int& gg = *i;

	bTests();

	EUS game;

	game.run();

	return 0;
}

void bTests() {
	EntityBuilder b;

	//b.createMap("Content\\test.txt");
}
