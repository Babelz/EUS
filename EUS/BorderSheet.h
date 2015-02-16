#pragma once
#include "NamedTileSheet.h"

class BorderSheet : public NamedTileSheet {
protected:
	void createSources();
public:
	BorderSheet(Texture* const texture, const size_t tileSize);

	~BorderSheet();
};

