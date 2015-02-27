#include "SpriteBatch.h"

SpriteBatch::SpriteBatch() : vertexArray(0),
							 vertexBuffer(0),
							 indexBuffer(0),
							 spritesCount(0),
							 isDrawing(false) {
	perspective = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
}

#pragma region Private members
void SpriteBatch::initializeShader() {
	ContentManager content("Content");
	shader = content.load<Effect>("basic");
}
void SpriteBatch::initializeBuffers() {
	for (size_t i = 0; i < INITIAL_BATCH_SIZE; i++) {
		spriteQueue.push_back(SpriteInfo());
	}

	batchSize = INITIAL_BATCH_SIZE;

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, position)));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, color)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)(offsetof(VertexPositionColorTexture, uv)));
	
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
}
void SpriteBatch::createIndices() {
	size_t indicesCount = MAX_BATCH_SIZE * INDICES_PER_SPRITE;

	for (size_t i = 0; i < indicesCount; i += VERTICES_PER_SPRITE) {
		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + 2);

		indices.push_back(i + 1);
		indices.push_back(i + 3);
		indices.push_back(i + 2);
	}
}
void SpriteBatch::renderBatch(Texture* const texture, const size_t first, const size_t last) {
	glBindTexture(GL_TEXTURE_2D, texture->getId());

	glDrawElements(
		GL_TRIANGLES,
		INDICES_PER_SPRITE * last - first,
		GL_UNSIGNED_SHORT,
		(void*)(first * INDICES_PER_SPRITE * sizeof(unsigned short)));

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SpriteBatch::generateVertices() {
	vertices.clear();

	for (size_t i = 0; i < spritesCount; i++) {
		SpriteInfo& sprite = spriteQueue[i];

		// Top left.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x - sprite.origin.x,
			sprite.position.y - sprite.origin.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			sprite.tLeftTexCoord.x,
			sprite.tLeftTexCoord.y));

		// Top right.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x + sprite.texture->width * sprite.xScale - sprite.origin.x,
			sprite.position.y - sprite.origin.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			sprite.tRightTexCoord.x,
			sprite.tRightTexCoord.y));

		// Bottom left.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x - sprite.origin.x,
			sprite.position.y + sprite.texture->height * sprite.yScale - sprite.origin.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			sprite.bLeftTexCoord.x,
			sprite.bLeftTexCoord.y));

		// Bottom right.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x + sprite.texture->width * sprite.xScale - sprite.origin.x,
			sprite.position.y + sprite.texture->height * sprite.yScale - sprite.origin.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			sprite.bRightTexCoord.x,
			sprite.bRightTexCoord.y));
	}
}

void SpriteBatch::sortBatch() {
	std::sort(spriteQueue.begin(), spriteQueue.begin() + spritesCount, [](SpriteInfo& a, SpriteInfo& b) {
		return a.texture->getId() < b.texture->getId();
	});
}
void SpriteBatch::flushBatch() {
	sortBatch();
	generateVertices();

	glActiveTexture(GL_TEXTURE0 + 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorTexture) * spritesCount * VERTICES_PER_SPRITE, vertices.data(), GL_DYNAMIC_DRAW);

	shader->bind();

	GLuint location = glGetUniformLocation(shader->getProgram(), "perspective");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(perspective));

	Texture* batchTexture = spriteQueue[0].texture;
	size_t first = 0;
	size_t last = 0;

	for (size_t i = 0; i < spritesCount; i++)	{
		Texture* texture = spriteQueue[i].texture;

		// Render whenever texture changes.
		if (texture != batchTexture) {
			// Flush from first to last.
			renderBatch(batchTexture, first, last);
			
			// Next render will start from this index.
			first = i;
		}
		
		batchTexture = texture;
		last = i;
	}

	renderBatch(batchTexture, first, last + 1);

	shader->unbind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void SpriteBatch::growSpriteQueue() {
	assert(batchSize + INITIAL_BATCH_SIZE <= MAX_BATCH_SIZE);

	for (size_t i = 0; i < INITIAL_BATCH_SIZE; i++){
		spriteQueue.push_back(SpriteInfo());
	}

	batchSize = spriteQueue.size();
}
#pragma endregion

#pragma region Public members
void SpriteBatch::initialize() {
	vertices.reserve(MAX_BATCH_SIZE * VERTICES_PER_SPRITE);

	createIndices();
	initializeShader();
	initializeBuffers();
}

void SpriteBatch::begin() {
	if (isDrawing) {
		throw std::logic_error("End must be called before begin.");
	}

	isDrawing = true;
}

void SpriteBatch::draw(Texture* const texture, pmath::Rectf& rect) {
	pmath::Vec3f position(rect.position.x, rect.position.y, 1.0f);

	float xScale = rect.size.x / texture->width;
	float yScale = rect.size.y / texture->height;

	draw(texture, position, pmath::Vec2f(0.0f, 0.0f), pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), xScale, yScale);
}
void SpriteBatch::draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec2f& origin, pmath::Vec4f& color, float xScale, float yScale) {
	if (spritesCount >= batchSize) {
		growSpriteQueue();
	}

	SpriteInfo& sprite = spriteQueue[spritesCount];

	sprite.position = position;
	sprite.origin = origin;
	sprite.texture = texture;
	sprite.color = color;

	sprite.xScale = xScale;
	sprite.yScale = yScale;

	sprite.tLeftTexCoord.x = 0.0f;
	sprite.tLeftTexCoord.y = 1.0f;

	sprite.tRightTexCoord.x = 1.0f;
	sprite.tRightTexCoord.y = 1.0f;

	sprite.bLeftTexCoord.x = 0.0f;
	sprite.bLeftTexCoord.y = 0.0f;

	sprite.bRightTexCoord.x = 1.0f;
	sprite.bRightTexCoord.y = 0.0f;

	spritesCount++;
}

void SpriteBatch::draw(Texture* const texture, pmath::Rectf& source, pmath::Vec3f& position, pmath::Vec4f color) {
	pmath::Rectf destination(position.x, position.y, source.size.x, source.size.y);

	draw(texture, source, destination, color);
}

static float f = 0.0f;

void SpriteBatch::draw(Texture* const texture, pmath::Rectf& source, pmath::Rectf& destionation, pmath::Vec4f color) {
	float xScale = destionation.size.x / texture->width;
	float yScale = destionation.size.y / texture->height;

	pmath::Vec3f position(destionation.position.x, destionation.position.y, 0.0f);

	draw(texture, position, pmath::Vec2(1.0f), color, xScale, yScale);
	
	// Set tex coords for last sprite.
	SpriteInfo& sprite = spriteQueue[spritesCount - 1];

	sprite.tLeftTexCoord.x = source.getLeft() / texture->width;
	sprite.tLeftTexCoord.y = source.getTop() / source.size.y;

	sprite.tRightTexCoord.x = source.getRight() / texture->width;
	sprite.tRightTexCoord.y = source.getTop() / source.size.y;

	sprite.bLeftTexCoord.x = source.getLeft() / texture->width;
	sprite.bLeftTexCoord.y = -(source.size.y / texture->height);

	sprite.bRightTexCoord.x = source.getRight() / texture->width;
	sprite.bRightTexCoord.y = -(source.size.y / texture->height);

	std::cout << f << std::endl;
}

void SpriteBatch::draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec4f& color, float scale) {
	draw(texture, position, pmath::Vec2f(0.0f, 0.0f), color, scale, scale);
}
void SpriteBatch::draw(Texture* const texture, pmath::Vec3f& position, pmath::Vec4f& color) {
	draw(texture, position, color, 1.0f);
}
void SpriteBatch::draw(Texture* const texture, pmath::Vec3f& position) {
	draw(texture, position, pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
}
void SpriteBatch::draw(Texture* const texture, float x, float y) {
	draw(texture, pmath::Vec3f(x, y, 1.0f), pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f), 1.0f);
}
void SpriteBatch::end() {
	if (!isDrawing) {
		throw std::logic_error("Begin must be called before end.");
	}

	if (spritesCount > 0) {
		flushBatch();
		spritesCount = 0;
	}

	isDrawing = false;
}
#pragma endregion

SpriteBatch::~SpriteBatch() {
	/*glDeleteBuffers(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);

	GLuint error = glGetError();
	assert(error == 0);*/
}