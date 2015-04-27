#include "ModelMapping.h"
#include "Require.h"

ModelMapping::ModelMapping(Game& game) : model(nullptr),
									     game(game) {
}

void ModelMapping::load(const std::string& filename) {
	const std::string TOKEN_MESH = "-mesh";
	const std::string TOKEN_MAPPINGS = "-mappings";

	std::string currentToken;

	std::ifstream inStream(filename);
	std::string line;

	StringHelper strHelper;

	require(inStream.is_open(), "MeshMapping: could not open file " + filename);

	while (std::getline(inStream, line))
	{
		strHelper.trim(line);

		if (!line.empty() && line[0] == '-') {
			// Token changed.
			currentToken = line;
			
			continue;
		}

		// No token, keep looking for a token.
		if (line.empty()) continue;
		
		std::vector<std::string> tokens;

		if (currentToken == TOKEN_MESH) {
			// Process mesh data.
			model = game.content().load<Model>(line);
		}
		else if (currentToken == TOKEN_MAPPINGS) {
			// Process source data.
			std::vector<std::string> tokens;

			strHelper.split(line, std::string(" "), tokens, true, StringSplitOptions::REMOVE_EMPTY);

			require(tokens.size() == 2, "MeshMapping: too many or too few tokens");

			// Load texture and create new mapping.
			Texture* texture = game.content().load<Texture>(tokens[0]);
			char ch = tokens[1][0];

			textures.insert(std::pair<char, Texture* const>(ch, texture));
		}
	}
}

Texture* const ModelMapping::getTexture(char key) const {
	return textures.at(key);
}
Model* const ModelMapping::getModel() const {
	return model;
}

ModelMapping::~ModelMapping() {
}