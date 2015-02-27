#pragma once
#include "MapGrid.h"
#include "StringHelper.h"
#include "Require.h"
#include <string>
#include <vector>
#include <fstream>

class MapLoader {
private:
	const std::string SCOPE_TOKEN = "-tiles";

	std::vector<std::vector<char>> chars;

	std::string sheetName;
	std::string mapName;

	size_t mapHeight;
	size_t mapWidth;
public:
	MapLoader();

	void load(const std::string& filename);

	const std::string& getSheetName() const;
	const std::string& getMapName() const;

	const size_t getMapHeight() const;
	const size_t getMapWidth() const;

	char charAt(const size_t i, const size_t j);

	~MapLoader();
};

