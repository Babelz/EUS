#pragma once
#include "Entity.h"

class TileEngine : public Component {
private:
	int m_mapWidth;
	int m_mapHeight;
	
	int m_tileSize;
public:
	TileEngine(Game& game, Entity& owner, const int mapWidth, const int mapHeight,
										  const int tileSize);

	const int mapWidthInTiles() const;
	const int mapHeightInTiles() const;

	const int mapWidthInPixels() const;
	const int mapHeightInPixels() const;

	const int tileSize() const;

	~TileEngine();
};

