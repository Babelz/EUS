#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() : spritePointer(0), vertexPointer(0) {
	vertexBuffer = vertexArray = indexBuffer = 0;

	initIndicies();
	initBuffers();

	// Initialize shaders.
	ContentManager content("Content");
	shader = content.load<Effect>("basic");

	vertices.reserve(batchSize * verticesPerSprite);
}

#pragma region Private members
void SpriteBatch::initIndicies() {
	for (unsigned short i = 0; i < batchSize * indicesPerSprite; i += verticesPerSprite) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}
}
void SpriteBatch::initBuffers() {
	// Generate vertex array.
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Vertex buffer init.
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Position attribs.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));

	// Color attribs.
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, color));
	
	// UV attribs.
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, uv));

	// Create index buffer.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

void SpriteBatch::renderBatch(SpriteInfo& sprite) {
}
void SpriteBatch::prepRendering() {
	// Clear buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, spritePointer * verticesPerSprite * sizeof(VertexPositionColorTexture), nullptr, GL_DYNAMIC_DRAW);
}
void SpriteBatch::flushBatch() {
	// TODO: do sorting etc, just try to get it working first..
	for (unsigned int i = 0; i < spritePointer; i++) {
		renderBatch(sprites[i]);
	}
}
#pragma endregion

#pragma region Public members
void SpriteBatch::draw(Texture* const texture, const pmath::Vec3f& position, const pmath::Vec4f& color) {
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
}
