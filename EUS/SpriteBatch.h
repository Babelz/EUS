#pragma once
#include "GL\glew.h"
#include "Resources.h"
#include "Vector.hpp"
#include "Content.h"
#include "VertexColorPositionTexture.h"
#include <algorithm>
#include <cassert>
#include <vector>
#include <GLM.h>

struct SpriteInfo {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;

	Texture* texture;
};

class SpriteBatch {
private:
	// Max size in sprites.
	const size_t MAX_BATCH_SIZE = 256;
	// Initial size of the batch.
	const size_t INITIAL_BATCH_SIZE = 64;

	const unsigned short INDICES_PER_SPRITE = 6;
	const unsigned short VERTICES_PER_SPRITE = 4;

	size_t batchSize;
	size_t spritesCount;

	bool isDrawing;

	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint indexBuffer;

	glm::mat4 projection;
	glm::mat4 world;
	glm::mat4 view;
	glm::mat4 perspective;

	Effect* shader;

	std::vector<unsigned short> indices;
	std::vector<SpriteInfo> spriteQueue;
	
	void initializeShader();
	void initializeBuffers();
	void createIndices();

	void sortBatch();
	void renderBatch(Texture* const texture, const size_t& first, const size_t& last);
	void flushBatch();

	void growSpriteQueue();
public:
	SpriteBatch();

	// TODO: for testing..
	void draw();

	void begin();
	void draw(Texture* texture, pmath::Vec3f& position, pmath::Vec4f& color);
	void end();

	~SpriteBatch();
};

