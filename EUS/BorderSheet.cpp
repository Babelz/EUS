#include "BorderSheet.h"

BorderSheet::BorderSheet(Texture* const texture, const size_t tileSize) : NamedTileSheet(texture, tileSize) {
}

#pragma region Protected members
void BorderSheet::createSources() {
	pushSource("plains", 0, 0);
	pushSource("factory", 32, 0);
	pushSource("city", 64, 0);
	pushSource("hills", 96, 0);
}
#pragma endregion

BorderSheet::~BorderSheet() {
}
