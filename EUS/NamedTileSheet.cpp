#include "NamedTileSheet.h"


NamedTileSheet::NamedTileSheet(Texture* const texture, size_t tileSize) : texture(texture),
																	      tileSize(tileSize) {
}

#pragma region Protected members
void NamedTileSheet::pushSource(const std::string& name, int x, int y) {
	sources.insert(std::pair<std::string, pmath::Rectf>(name, pmath::Rectf(x * tileSize, y * tileSize, tileSize, tileSize)));
}
#pragma endregion

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
	createSources();

	assert(sources.size() > 0);
}
#pragma endregion

NamedTileSheet::~NamedTileSheet() {
}
