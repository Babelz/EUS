#pragma once
#include <algorithm>
#include <cassert>
#include <vector>
#include <GLM.h>
#include "GL\glew.h"
#include "Resources.h"
#include "Vector.hpp"
#include "Rectangle.hpp"
#include "Content.h"
#include "VertexColorPositionTexture.h"

struct SpriteInfo {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;
	pmath::Vec2f origin;

	float rotation;
	float xScale;
	float yScale;

	Texture* texture;
};

class SpriteBatch {
private:
	// Max size in sprites.
	const size_t MAX_BATCH_SIZE = 4096;
	// Initial size of the batch.
	const size_t INITIAL_BATCH_SIZE = 256;

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
	std::vector<VertexPositionColorTexture> vertices;
	
	void initializeShader();
	void initializeBuffers();
	void createIndices();

	void generateVertices();

	void sortBatch();
	void renderBatch(Texture* const texture, const size_t& first, const size_t& last);
	void flushBatch();

	void growSpriteQueue();
public:
	SpriteBatch();

	void initialize();

	void begin();
	
	void draw(Texture* const texture, pmath::Rectf& rect);
	void draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec2f& origin, pmath::Vec4f& color, float xScale, float yScale);
	void draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec4f& color, float scale);
	void draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec4f& color);
	void draw(Texture* const texture, pmath::Vec3f& position);
	void draw(Texture* const texture, float x, float y);

	void end();

	~SpriteBatch();
};

