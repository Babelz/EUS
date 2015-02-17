#pragma once
#include "StringHelper.h"
#include <cassert>
#include <algorithm>
#include <string>
#include <fstream>
#include <map>

// TODO: change that data is loaded from a file.
//       atm its hard coded.

class SheetMapping {
private:
	const std::string SCOPE_TOKEN = "-mappings";

	std::map<char, std::string> mappings;

	void pushMapping(char ch, const std::string& name);
public:
	SheetMapping();

	std::string& getTileName(char ch);

	void load(const std::string& filename);

	~SheetMapping();
};

