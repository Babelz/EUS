#include "NamedTileSheet.h"


NamedTileSheet::NamedTileSheet(const std::string& name, Texture* const texture, size_t tileSize) : name(name),
																								   texture(texture),
																								   tileSize(tileSize) {
	createSources(sources);
}

#pragma region Public members
Texture* const NamedTileSheet::getTexture() const {
	return texture;
}
size_t NamedTileSheet::getTileSize() const {
	return tileSize;
}

void NamedTileSheet::getSource(const std::string& name, pmath::Rectf& outRect) const {
	outRect = sources.at(name);
}
#pragma endregion

NamedTileSheet::~NamedTileSheet() {
}
