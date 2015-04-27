#pragma once
#include <map>
#include <string>
#include "Resources.h"
#include "Game.h"

// Class for containing textures and meshes.
class ModelMapping {
private:
	Model* model;
	Game& game;

	std::map<char, Texture* const> textures;
public:
	ModelMapping(Game& game);
	
	void load(const std::string& filename);
	
	Texture* const getTexture(char key) const;
	Model* const getModel() const;

	~ModelMapping();
};

