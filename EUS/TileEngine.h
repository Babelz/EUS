#pragma once
#include "Entity.h"

class TileEngine : public Component {
private:
	int m_mapWidth;
	int m_mapHeight;
	
	int m_tileWidth;
	int m_tileHeight;
public:
	TileEngine(Game& game, Entity& owner, const int mapWidth, const int mapHeight,
										  const int tileWidth, const int tileHeight);

	const int mapWidthInTiles() const;
	const int mapHeightInTiles() const;

	const int mapWidthInPixels() const;
	const int mapHeightInPixels() const;

	const int tileWidth() const;
	const int tileHeight() const;

	~TileEngine();
};

