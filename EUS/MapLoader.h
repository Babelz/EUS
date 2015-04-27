#pragma once
#include "MapGrid.h"
#include "StringHelper.h"
#include "Require.h"
#include <string>
#include <vector>
#include <fstream>
#include "TileLoader.h"

class MapLoader {
private:
	TileLoader loader;

	std::string sheetName;
	std::string mapName;
public:
	MapLoader(Game& game);

	void load(const std::string& filename);

	const std::string& getSheetName() const;
	const std::string& getMapName() const;

	const size_t getMapHeight() const;
	const size_t getMapWidth() const;

	char charAt(const size_t i, const size_t j);

	~MapLoader();
};

