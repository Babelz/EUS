#include "MapLoader.h"

MapLoader::MapLoader(Game& game) : loader(TileLoader(game)) {
}

#pragma region Public members
void MapLoader::load(const std::string& filename) {
	loader.load(filename);
}
const std::string& MapLoader::getSheetName() const  {
	return sheetName;
}
const std::string& MapLoader::getMapName() const  {
	return mapName;
}

const size_t MapLoader::getMapHeight() const {
	return loader.getRows();
}
const size_t MapLoader::getMapWidth() const {
	return loader.getColumns();
}

// i = row
// j = column
char MapLoader::charAt(const size_t i, const size_t j) {
	return loader.charAt(i, j);
}
#pragma endregion

MapLoader::~MapLoader() {
}
