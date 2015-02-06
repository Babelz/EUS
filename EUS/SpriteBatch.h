#pragma once
#include "GL\glew.h"
#include "Resources.h"
#include "Vector.hpp"
#include <cassert>

struct SpriteInfo {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;

	Texture* texture;
};

class SpriteBatch {
private:
	const int batchSize = 1024;
	const int verticesPerSprite = 4;
	const int indicesPerSprite = 6;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint indexBuffer;

	Effect* effect;

	int spritePointer;

	SpriteInfo* sprites;
	unsigned short* indicies;
	float* vertices;

	bool rendering;

	void allocSprites();
	void initIndicies();
	void initVertices();
	void initBuffers();

	void renderBatch();
	void flushBatch();

	// TODO: need sorting
	// void sortSprites();
public:
	SpriteBatch();

	void draw(Texture* const texture, pmath::Vec3f& const position, pmath::Vec4f& const color);

	void begin();
	void end();

	~SpriteBatch();
};

