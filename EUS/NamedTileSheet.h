#pragma once
#include <map>
#include "Resources.h"
#include "Rectangle.hpp"

class NamedTileSheet {
private:
	size_t tileSize;
	Texture* texture;

	std::map<std::string, pmath::Rectf> sources;
protected:
	virtual void createSources(std::map<std::string, pmath::Rectf>& sources) = 0;
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

