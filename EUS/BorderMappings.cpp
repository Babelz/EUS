#include "BorderMappings.h"

BorderMappings::BorderMappings() : SheetMapping() {
}

#pragma region Protected members
void BorderMappings::createMappings() {
	pushMapping('#', "plains");
	pushMapping('$', "factory");
	pushMapping('T', "city");
	pushMapping('^', "hills");
}
#pragma endregion

BorderMappings::~BorderMappings() {
}
