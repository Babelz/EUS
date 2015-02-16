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
void SheetMapping::initialize() {
	createMappings();

	assert(mappings.size() > 0);
}
#pragma endregion

SheetMapping::~SheetMapping() {
}
