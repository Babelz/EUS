#include "TileEngine.h"

TileEngine::TileEngine(Game& game, Entity& owner, const int mapWidth, const int mapHeight,
												  const int tileSize) : Component(game, owner, 0),
																	    m_mapWidth(mapWidth),
															            m_mapHeight(mapHeight),
														                m_tileSize(tileSize) {
}

#pragma region Public members
const int TileEngine::mapWidthInTiles() const {
	return m_mapWidth;
}
const int TileEngine::mapHeightInTiles() const {
	return m_mapHeight;
}

const int TileEngine::mapWidthInPixels() const {
	return m_mapWidth * m_tileSize;
}
const int TileEngine::mapHeightInPixels() const {
	return m_mapHeight * m_tileSize;
}

const int TileEngine::tileSize() const {
	return m_tileSize;
}
#pragma endregion

TileEngine::~TileEngine() {
}
