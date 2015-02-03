#pragma once
#include <vector>
#include <string>
#include <algorithm>

class TagContainer {
private:
	std::vector<std::string> tags;

	int indexOf(std::string tag) const;
public:
	TagContainer();

	bool isTagged(std::string tag) const;
	bool unTag(std::string tag);
	bool tag(std::string tag);

	~TagContainer();
};

