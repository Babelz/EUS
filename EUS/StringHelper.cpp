#include "StringHelper.h"

StringHelper::StringHelper() {
}

#pragma region Public memebers
bool StringHelper::contains(const std::string& line, const std::string& pattern) const {
	return line.find(pattern) != std::string::npos;
}

void StringHelper::trimStart(std::string& line) const {
	if (line[0] != ' ') return;

	size_t i = 0;

	do {
		if (i + 1 >= line.size()) return;

		i++;
	} while (line[i] == ' ');

	line = line.substr(i, line.size() - i);
}

void StringHelper::trimEnd(std::string& line) const {
	if (line[line.size() - 1] != ' ') return;

	int i = static_cast<int>(line.size());

	do {
		if (i - 1 < 0) return;
		
		i--;
	} while (line[i] == ' ');

	line = line.substr(0, i + line.size());
}

void StringHelper::trim(std::string& line) const {
	trimStart(line);
	trimEnd(line);
}

void StringHelper::split(const std::string& const line, const std::string& token, std::vector<std::string>& results, bool trimResults) {
	size_t start = 0;
	size_t end = line.find(token);

	while (end != std::string::npos) {
		std::string sub = line.substr(start, end - start);

		if (trimResults) {
			trim(sub);
		}

		results.push_back(sub);

		start = end + token.size();
		end = line.find(token, start);
	}

	std::string sub = line.substr(start, end - start);

	if (trimResults) {
		trim(sub);
	}

	results.push_back(sub);
}
#pragma endregion 

StringHelper::~StringHelper() {
}