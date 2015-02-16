#pragma once
#include <map>
#include "Resources.h"
#include "Rectangle.hpp"

// TODO: change that data is loaded from a file.
//       atm its hard coded.

class NamedTileSheet {
private:
	size_t tileSize;
	Texture* texture;

	std::map<std::string, pmath::Rectf> sources;
protected:
	void pushSource(const std::string& name, int x, int y);

	virtual void createSources() = 0;
public:
	NamedTileSheet(Texture* const texture, const size_t tileSize);
	
	Texture* const getTexture() const;
	size_t getTileSize() const;
	std::string& getName();

	void getSource(const std::string& name, pmath::Rectf& outRect) const;
	bool containsSourceWithName(const std::string& name) const;

	void initialize();

	~NamedTileSheet();
};

