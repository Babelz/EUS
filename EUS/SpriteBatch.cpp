#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() {
	allocSprites();
	initIndicies();
	initVertices();
	initBuffers();
}

#pragma region Private members
void SpriteBatch::allocSprites() {
	sprites = new SpriteInfo[batchSize];
}
void SpriteBatch::initIndicies() {
	indicies = new unsigned short[indicesPerSprite * batchSize];

#ifdef _DEBUG
	int index = 0;
#endif

	for (unsigned short i = 0; i < batchSize * indicesPerSprite; i++) {
		indicies[i] = i;
		indicies[i + 1] = i + 1;
		indicies[i + 2] = i + 2;

		indicies[i + 3] = i + 1;
		indicies[i + 4] = i + 3;
		indicies[i + 2] = i + 2;

#ifdef _DEBUG
		index = i;
#endif
	}

#ifdef _DEBUG
	int len = indicesPerSprite * batchSize;
	
	assert(len - 1 == index);
#endif
}
void SpriteBatch::initVertices() {
	vertices = new float[verticesPerSprite * batchSize];

	for (int i = 0; i < verticesPerSprite * batchSize; i++) {
		vertices[i] = 0.0f;
	}
}
void SpriteBatch::initBuffers() {
	// Generate vertex array.
	vertexArray = 0;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Vertex buffer init.
	vertexBuffer = 0;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

	// Position attribs.
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Color attribs.
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, offsetof(SpriteInfo, color), (void*)0);
	
	// UV attribs.
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, offsetof(SpriteInfo, uv), (void*)0);

	// Create index buffer.
	indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6, &indicies, GL_DYNAMIC_DRAW);

	// Initialize shaders.
	ContentManager
}


void SpriteBatch::renderBatch() {

}
void SpriteBatch::flushBatch() {

}
#pragma endregion

#pragma region Public members
void SpriteBatch::draw(Texture* const texture, pmath::Vec3f& const position, pmath::Vec4f& const color) {
	SpriteInfo& sprite = sprites[spritePointer];
	sprite.texture = texture;
	// Set position values.
	sprite.position = pmath::Vec3f(position);
	// Set color values.
	sprite.color = pmath::Vec4f(color);
	// Set uv values.
	sprite.uv.x = 1.0f;
	sprite.uv.y = 1.0f;

	spritePointer++;
}

void SpriteBatch::begin() {
	if (rendering) {
		throw std::logic_error("End must be called before begin.");
	}

	rendering = true;
}
void SpriteBatch::end() {
	if (!rendering) {
		throw std::logic_error("Begin must be called before end.");
	}

	rendering = false;

	flushBatch();
}
#pragma endregion

SpriteBatch::~SpriteBatch() {
	delete[] sprites;
	delete[] indicies;
	delete[] vertices;
}
