#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

/*
	Steps of creating a map

	1) Create tilesheet
	2) Create mappings for tiles
	3) Create tile builder

	4) Load tile data from file
	5) Initialize tiles from it using
	   mappings and tile builder
*/

class MapLoader {
private:
	std::vector<char> chars;

	std::string sheetName;
	std::string mapName;

	size_t mapHeight;
	size_t mapWidth;
public:
	MapLoader();

	void load(const std::string& filename);

	std::string& getSheetName();
	std::string& getMapName();

	size_t getMapHeight() const;
	size_t getMapWidth() const;

	char charAt(const size_t i, const size_t j);

	~MapLoader();
};

