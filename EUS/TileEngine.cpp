#include "TileEngine.h"

TileEngine::TileEngine(Game& game, Entity& owner, const int mapWidth, const int mapHeight,
												  const int tileWidth, const int tileHeight) : Component(game, owner, 0),
																							   m_mapWidth(mapWidth),
																							   m_mapHeight(mapHeight),
																							   m_tileWidth(tileWidth),
																							   m_tileHeight(tileHeight) {
}

#pragma region Public members
const int TileEngine::mapWidthInTiles() const {
	return m_mapWidth;
}
const int TileEngine::mapHeightInTiles() const {
	return m_mapHeight;
}

const int TileEngine::mapWidthInPixels() const {
	return m_mapWidth * m_tileWidth;
}
const int TileEngine::mapHeightInPixels() const {
	return m_mapHeight * m_tileHeight;
}

const int TileEngine::tileWidth() const {
	return m_tileWidth;
}
const int TileEngine::tileHeight() const {
	return m_tileHeight;
}
#pragma endregion

TileEngine::~TileEngine() {
}
