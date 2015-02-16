#include "SheetMapping.h"

SheetMapping::SheetMapping() {
}

#pragma region Public members
std::string& SheetMapping::getTileName(char ch) {
	return mappings.at(ch);
}
void SheetMapping::initialize() {
	createMappings(mappings);
}
#pragma endregion

SheetMapping::~SheetMapping() {
}
