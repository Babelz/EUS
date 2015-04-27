#pragma once
#include <vector>
#include "Game.h"

class TileLoader {
private:
	const std::string SCOPE_TOKEN = "-tiles";

	Game& game;

	std::vector<std::vector<char>> chars;

	size_t rows;
	size_t columns;
public:
	TileLoader(Game& game);

	void load(const std::string& filename);

	const char charAt(const size_t i, const size_t j) const;

	const size_t getRows() const;
	const size_t getColumns() const;

	~TileLoader();
};

