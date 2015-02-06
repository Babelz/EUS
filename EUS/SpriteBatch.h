#pragma once
#include "GL\glew.h"

struct SpriteInfo {

};

class SpriteBatch {
private:
	const int initialBatchSize = 64;
	const int maxBatchSize = 1024;
	const int verticesPerSprite = 4;
	const int indicesPerSprite = 6;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint indexBuffer;

	int spritePointer;

	SpriteInfo** sprites;
	short** indicies;
	float** vertices;

	bool rendering;
public:
	SpriteBatch();

	void begin();
	void end();

	~SpriteBatch();
};

