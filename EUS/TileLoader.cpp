#include "TileLoader.h"

TileLoader::TileLoader(Game& game) : game(game),
									 rows(0),
									 columns(0) {
}

#pragma region Public members
void TileLoader::load(const std::string& filename) {
	std::ifstream inStream(filename, std::ios::in);

	require(inStream.is_open(), "TileLoader: could not open file " + filename);

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

			chars[rows].push_back(ch);
		}

		if (columns < line.size()) {
			columns = line.size();
		}

		rows++;
	}

	inStream.close();
}

const char TileLoader::charAt(const size_t i, const size_t j) const {
	return chars[i][j];
}

const size_t TileLoader::getRows() const {
	return rows;
}
const size_t TileLoader::getColumns() const {
	return columns;
}
#pragma endregion

TileLoader::~TileLoader() {
}
