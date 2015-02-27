#include "Require.h"

void require(const bool condition, const std::string& message) {
	if (!condition) {
		throw std::logic_error(message);
	}
}