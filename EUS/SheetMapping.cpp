#include "SheetMapping.h"

SheetMapping::SheetMapping() {
}

#pragma region Protected members
void SheetMapping::pushMapping(char ch, const std::string& name) {
	mappings.insert(std::pair<char, std::string>(ch, name));
}
#pragma endregion

#pragma region Public members
std::string& SheetMapping::getTileName(char ch) {
	return mappings.at(ch);
}
void SheetMapping::load(const std::string& filename) {
	if (mappings.size() > 0) {
		mappings.clear();
	}

	std::ifstream inStream(filename);
	std::string line;

	StringHelper strHelper;

	assert(inStream.is_open());

	// Skip to mappings.
	while (std::getline(inStream, line)) { 
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			line.clear();

			break;
		}
	}

	// Read mappings.
	while (std::getline(inStream, line)) {
		if (strHelper.contains(line, SCOPE_TOKEN)) {
			break;
		}

		std::vector<std::string> tokens;
		strHelper.split(line, std::string(" "), tokens, true);

		assert(tokens.size() == 2);

		pushMapping(tokens[0][0], tokens[1]);
	}

	inStream.close();
}
#pragma endregion

SheetMapping::~SheetMapping() {
}
