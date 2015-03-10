#include "TileEngine.h"

TileEngine::TileEngine(Game& game, Entity& owner, const size_t mapWidth, const size_t mapHeight, const size_t tileSize) : Component(game, owner, 0),
																														  m_mapWidth(mapWidth),
																														  m_mapHeight(mapHeight),
																														  m_tileSize(tileSize) {
}

#pragma region Public members
const size_t TileEngine::mapWidthInTiles() const {
	return m_mapWidth;
}
const size_t TileEngine::mapHeightInTiles() const {
	return m_mapHeight;
}

const size_t TileEngine::mapWidthInPixels() const {
	return m_mapWidth * m_tileSize;
}
const size_t TileEngine::mapHeightInPixels() const {
	return m_mapHeight * m_tileSize;
}

const size_t TileEngine::tileSize() const {
	return m_tileSize;
}
#pragma endregion

TileEngine::~TileEngine() {
}
