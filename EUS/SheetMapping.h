#pragma once
#include "NamedTileSheet.h"
#include <algorithm>	
#include <string>
#include <map>

// TODO: change that data is loaded from a file.
//       atm its hard coded.

class SheetMapping {
private:
	std::map<char, std::string> mappings;
protected:
	void pushMapping(char ch, const std::string& name);

	virtual void createMappings() = 0;
public:
	SheetMapping();

	std::string& getTileName(char ch);
	void initialize();

	~SheetMapping();
};

