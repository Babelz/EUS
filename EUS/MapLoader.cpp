#include "MapLoader.h"

MapLoader::MapLoader() : mapWidth(0),
						 mapHeight(0) {
}

#pragma region Public members
void MapLoader::load(const std::string& filename) {
	std::ifstream inStream(filename, std::ios::in);

	require(inStream.is_open(), "MapLoader: could not open file " + filename);

	StringHelper strHelper;
	std::string line;
	
	while (std::getline(inStream, line)) {
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			line.clear();

			break;
		}
	}
	

	while (std::getline(inStream, line))
	{
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			break;
		}

		if (line.empty()) {
			continue;
		}

		chars.push_back(std::vector<char>());

		strHelper.trim(line);

		for (size_t i = 0; i < line.size(); i++) {
			char ch = line[i];

			require(ch != ' ', "MapLoader: illegal character");
			
			chars[mapHeight].push_back(ch);
		}

		if (mapWidth < line.size()) {
			mapWidth = line.size();
		}

		mapHeight++;
	}

	inStream.close();
}
const std::string& MapLoader::getSheetName() const  {
	return sheetName;
}
const std::string& MapLoader::getMapName() const  {
	return mapName;
}

const size_t MapLoader::getMapHeight() const {
	return mapHeight;
}
const size_t MapLoader::getMapWidth() const {
	return mapWidth;
}

// i = row
// j = column
char MapLoader::charAt(const size_t i, const size_t j) {
	return chars[i][j];
}
#pragma endregion

MapLoader::~MapLoader() {
}
