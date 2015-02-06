#pragma once
#include "GL\glew.h"
#include "Resources.h"
#include "Vector.hpp"
#include "Content.h"
#include "VertexColorPositionTexture.h"
#include <cassert>
#include <vector>

struct SpriteInfo {
	pmath::Vec3f position;
	pmath::Vec4f color;
	
	float rotation;

	Texture* texture;

	SpriteInfo::SpriteInfo() {
		texture = 0;
	}
};

class SpriteBatch {
private:
	const int batchSize = 1024;
	const int verticesPerSprite = 4;
	const int indicesPerSprite = 6;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint indexBuffer;

	Effect* shader;

	unsigned int spritePointer;
	unsigned int vertexPointer;
	unsigned int flushPointer;

	SpriteInfo* sprites;
	std::vector<unsigned short> indices;
	VertexPositionColorTexture* vertices;

	bool rendering;

	void allocSprites();
	void initIndicies();
	void initVertices();
	void initBuffers();

	void renderBatch(SpriteInfo* const sprite);
	void flushBatch();
public:
	SpriteBatch();

	void draw(Texture* const texture, const pmath::Vec3f& position, const pmath::Vec4f& color);

	void begin();
	void end();

	~SpriteBatch();
};

