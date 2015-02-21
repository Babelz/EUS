#pragma once
#include <string>
#include <vector>

class StringHelper {
public:
	StringHelper();

	bool contains(const std::string& line, const std::string& pattern) const;

	void trimStart(std::string& line) const;

	void trimEnd(std::string& line) const;

	void trim(std::string& line) const;

	void split(const std::string& line, const std::string& token, std::vector<std::string>& results, const bool trimResults = false);

	~StringHelper();
};