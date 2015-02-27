#pragma once
#include "StringHelper.h"
#include "Resources.h"
#include "Rectangle.hpp"
#include "Require.h"
#include <fstream>	
#include <map>

class NamedTileSheet {
private:
	const std::string SCOPE_TOKEN = "-sources";

	size_t tileSize;
	Texture* texture;

	std::map<std::string, pmath::Rectf> sources;

	void pushSource(const std::string& name, int x, int y);
public:
	NamedTileSheet(Texture* const texture, const size_t tileSize);
	
	Texture* const getTexture() const;
	size_t getTileSize() const;
	std::string& getName();

	pmath::Rectf getSource(const std::string& name) const;
	bool containsSourceWithName(const std::string& name) const;

	void load(const std::string& filename);

	~NamedTileSheet();
};

