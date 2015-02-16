#include "MapLoader.h"

MapLoader::MapLoader() : mapWidth(0),
						 mapHeight(0) {
}

#pragma region Public members
void MapLoader::load(const std::string& filename) {
	std::ifstream inFile(filename, std::ios::in);

	assert(inFile.is_open());

	// Just read all chars. File should only contain tile data.
	std::string line;

	while (std::getline(inFile, line))
	{
		if (line.empty()) {
			continue;
		}

		mapHeight++;

		for (size_t i = 0; i < line.size(); i++) {
			char ch = line[i];

			assert(ch != ' ');
			
			chars.push_back(ch);
		}

		if (mapWidth < line.size()) {
			mapWidth = line.size();
		}
	}

	inFile.close();
}
std::string& MapLoader::getSheetName() {
	return sheetName;
}
std::string& MapLoader::getMapName() {
	return mapName;
}

size_t MapLoader::getMapHeight() const {
	return mapHeight;
}
size_t MapLoader::getMapWidth() const {
	return mapWidth;
}

char MapLoader::charAt(const size_t i, const size_t j) {
	return chars[i * j];
}
#pragma endregion

MapLoader::~MapLoader() {
}
