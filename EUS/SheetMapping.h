#pragma once
#include "NamedTileSheet.h"
#include <algorithm>	
#include <string>
#include <map>

class SheetMapping {
private:
	std::map<char, std::string> mappings;
protected:
	virtual void createMappings(std::map<char, std::string>& mappings) = 0;
public:
	SheetMapping();

	std::string& getTileName(char ch);
	void initialize();

	~SheetMapping();
};

