#pragma once
#include "TileBuilder.h"

class BorderTileBuilder : public TileBuilder {
protected:
	Entity* createFlats() const;
	Entity* createHills() const;

	void createBuilders();
public:
	BorderTileBuilder();
	
	~BorderTileBuilder();
};

