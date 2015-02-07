#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() : spritePointer(0), vertexPointer(0), flushPointer(0) {
	allocSprites();
	initIndicies();
	initVertices();
	initBuffers();
}

#pragma region Private members
void SpriteBatch::allocSprites() {
	sprites = new SpriteInfo[batchSize];

	for (int i = 0; i < batchSize; i++) {
		sprites[i] = SpriteInfo();
	}
}
void SpriteBatch::initIndicies() {
#ifdef _DEBUG
	int index = 0;
#endif

	for (unsigned short i = 0; i < batchSize * indicesPerSprite; i += verticesPerSprite) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
#ifdef _DEBUG
		index = i;
#endif
	}

#ifdef _DEBUG
	int len = indicesPerSprite * batchSize;
	
	//assert(len - 1 == index);
#endif
}
void SpriteBatch::initVertices() {
	vertices = new VertexPositionColorTexture[verticesPerSprite * batchSize];

	for (int i = 0; i < verticesPerSprite * batchSize; i++) {
		vertices[i] = VertexPositionColorTexture();
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
	glBufferData(GL_ARRAY_BUFFER, verticesPerSprite * batchSize, vertices, GL_DYNAMIC_DRAW);

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
	indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Initialize shaders.
	ContentManager content("Content");

	shader = content.load<Effect>("basic");
}

void SpriteBatch::renderBatch(SpriteInfo* const sprite) {
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, sprite->texture->getId());

	shader->bind();

	static float transform[] = {
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	/*static const VertexPositionColorTexture points[] = {
			VertexPositionColorTexture(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
			VertexPositionColorTexture(0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.f, 1.f),
			VertexPositionColorTexture(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.f, 0.f),
			VertexPositionColorTexture(0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.f, 0.f)
	};*/

	vertices[vertexPointer++] = VertexPositionColorTexture(sprite->position.x,
														   sprite->position.y,
														   sprite->position.z,
														   sprite->color.r,
														   sprite->color.g,
														   sprite->color.b,
														   sprite->color.a,
														   0.0f,
														   1.0f);

	
	vertices[vertexPointer++] = VertexPositionColorTexture(sprite->position.x + 0.5f,
														   sprite->position.y,
														   sprite->position.z,
														   sprite->color.r,
														   sprite->color.g,
														   sprite->color.b,
														   sprite->color.a,
														   1.0f,
														   1.0f);

	vertices[vertexPointer++] = VertexPositionColorTexture(sprite->position.x,
														   sprite->position.y + 0.5f,
														   sprite->position.z,
														   sprite->color.r,
														   sprite->color.g,
														   sprite->color.b,
														   sprite->color.a,
														   0.0f,
														   0.0f);

	vertices[vertexPointer++] = VertexPositionColorTexture(sprite->position.x + 0.5f,
														   sprite->position.y + 0.5f,
													       sprite->position.z,
														   sprite->color.r,
														   sprite->color.g,
														   sprite->color.b,
														   sprite->color.a,
														   1.0f,
														   0.0f);

	glBufferSubData(GL_ARRAY_BUFFER, flushPointer * sizeof(VertexPositionColorTexture), sizeof(VertexPositionColorTexture) * verticesPerSprite, vertices);

	//glBindVertexArray(0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	
	shader->unbind();
}
void SpriteBatch::flushBatch() {
	if (spritePointer != 0) {
		for (unsigned int i = 0; i < spritePointer; i++) {
			renderBatch(&sprites[i]);
		}
	}

	spritePointer = 0;
	vertexPointer = 0;
	flushPointer = 0;
}
#pragma endregion

#pragma region Public members
void SpriteBatch::draw(Texture* const texture, const pmath::Vec3f& position, const pmath::Vec4f& color) {
	SpriteInfo& sprite = sprites[spritePointer];
	sprite.texture = texture;
	// Set position values.
	sprite.position = pmath::Vec3f(position);
	// Set color values.
	sprite.color = pmath::Vec4f(color);
	// Set uv values.

	std::cout << sprites[spritePointer].position << std::endl;

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
	delete[] vertices;
}
