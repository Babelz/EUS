#include "NamedTileSheet.h"


NamedTileSheet::NamedTileSheet(Texture* const texture, size_t tileSize) : texture(texture),
																	      tileSize(tileSize) {
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
bool NamedTileSheet::containsSourceWithName(const std::string& name) const {
	auto iter = sources.find(name);

	return iter != sources.end();
}

void NamedTileSheet::initialize() {
	createSources(sources);
}
#pragma endregion

NamedTileSheet::~NamedTileSheet() {
}
