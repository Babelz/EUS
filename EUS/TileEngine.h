#pragma once
#include "Entity.h"

class TileEngine : public Component {
private:
	size_t m_mapWidth;
	size_t m_mapHeight;
	
	size_t m_tileSize;
public:
	TileEngine(Game& game, Entity& owner, const size_t mapWidth, const size_t mapHeight, const size_t tileSize);

	const size_t mapWidthInTiles() const;
	const size_t mapHeightInTiles() const;

	const size_t mapWidthInPixels() const;
	const size_t mapHeightInPixels() const;

	const size_t tileSize() const;

	~TileEngine();
};

