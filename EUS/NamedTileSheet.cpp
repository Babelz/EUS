#include "NamedTileSheet.h"


NamedTileSheet::NamedTileSheet(Texture* const texture, size_t tileSize) : texture(texture),
																	      tileSize(tileSize) {
}

#pragma region Protected members
void NamedTileSheet::pushSource(const std::string& name, int x, int y) {
	sources.insert(std::pair<std::string, pmath::Rectf>(name, pmath::Rectf(static_cast<float>(x), 
																		   static_cast<float>(y),
																		   static_cast<float>(tileSize),
																		   static_cast<float>(tileSize))));
}
#pragma endregion

#pragma region Public members
Texture* const NamedTileSheet::getTexture() const {
	return texture;
}
size_t NamedTileSheet::getTileSize() const {
	return tileSize;
}

pmath::Rectf NamedTileSheet::getSource(const std::string& name) const {
	return sources.at(name);
}
bool NamedTileSheet::containsSourceWithName(const std::string& name) const {
	auto iter = sources.find(name);

	return iter != sources.end();
}

void NamedTileSheet::load(const std::string& filename) {
	if (sources.size() > 0) {
		sources.clear();
	}

	std::ifstream inStream(filename);
	std::string line;

	StringHelper strHelper;

	assert(inStream.is_open());

	// Skip to sources.
	while (std::getline(inStream, line)) {
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			line.clear();

			break;
		}
	}

	// Read sources.
	while (std::getline(inStream, line)) {
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			break;
		}

		std::vector<std::string> tokens;
		strHelper.split(line, std::string(" "), tokens, true);

		assert(tokens.size() == 3);

		std::string name = tokens[0];
		std::stringstream stream;
		int x, y;

		stream.str(tokens[1]);
		stream >> x;

		stream.clear();

		stream.str(tokens[2]);
		stream >> y;

		pushSource(name, x, y);
	}

	inStream.close();
}
#pragma endregion

NamedTileSheet::~NamedTileSheet() {
}
