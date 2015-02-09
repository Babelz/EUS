#include "SpriteBatch.h"


SpriteBatch::SpriteBatch() : vertexArray(0),
							 vertexBuffer(0),
							 indexBuffer(0),
							 spritesCount(0),
							 isDrawing(false) {
	createIndices();
	initializeShader();
	initializeBuffers();

	perspective = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
}

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
void SpriteBatch::renderBatch(SpriteInfo& sprite) {
	static const int COUNT = 1;

	GLuint location = glGetUniformLocation(shader->getProgram(), "perspective");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(perspective));

	glBindTexture(GL_TEXTURE_2D, sprite.texture->getId());

	for (int i = 0; i < COUNT; i++) {
		// Top left.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x,
			sprite.position.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			0.0f,
			1.0f));
		
		// Top right.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x + sprite.texture->width,
			sprite.position.y,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			1.0f,
			1.0f));
		
		// Bottom left.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x,
			sprite.position.y + sprite.texture->height,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			0.0f,
			0.0f));

		// Bottom right.
		vertices.push_back(VertexPositionColorTexture(
			sprite.position.x + sprite.texture->width,
			sprite.position.y + sprite.texture->height,
			sprite.position.z,
			sprite.color.x,
			sprite.color.y,
			sprite.color.z,
			sprite.color.w,
			1.0f,
			0.0f));
	}
}
void SpriteBatch::flushBatch() {

	auto asd = sizeof(VertexPositionColorTexture);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorTexture) * spritesCount * VERTICES_PER_SPRITE, nullptr, GL_DYNAMIC_DRAW);

	glActiveTexture(GL_TEXTURE0 + 0);

	shader->bind();

	for (size_t i = 0; i < spritesCount; i++)	{
		renderBatch(spriteQueue[i]);
	}

	// sizeof(unsigned short) != sizeof(unsigned int) you fucking moron, be more careful in the future..
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexPositionColorTexture) * vertices.size(), vertices.data());
	glDrawElements(GL_TRIANGLES, INDICES_PER_SPRITE * spritesCount, GL_UNSIGNED_SHORT, (void*)0);

	shader->unbind();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void SpriteBatch::growSpriteQueue() {
	assert(batchSize + INITIAL_BATCH_SIZE <= MAX_BATCH_SIZE);

	for (size_t i = 0; i < INITIAL_BATCH_SIZE; i++){
		spriteQueue.push_back(SpriteInfo());
	}
}

void SpriteBatch::draw() {
	ContentManager content("Content");
	Texture* texture = content.load<Texture>("tuksu");

	begin();
	auto pos = pmath::Vec3f(100.0f, 100.0f, -0.5f);
	auto clr = pmath::Vec4f(1.0f, 1.0f, 1.0f, 1.0f);

	draw(texture, pos, clr);

	for (size_t i = 0; i < 10; i++)
	{
		pos.x += 10.0f * i;
		pos.y += 5.0f * i;
		draw(texture, pos, clr);
	}
	
	content.unloadAll();

	end();
}

void SpriteBatch::begin() {
	if (isDrawing) {
		return;
	}

	isDrawing = true;
}
void SpriteBatch::draw(Texture* texture, pmath::Vec3f& position, pmath::Vec4f& color) {
	if (spritesCount >= batchSize) {
		growSpriteQueue();
	}
	
	SpriteInfo& sprite = spriteQueue[spritesCount];

	sprite.position = position;
	sprite.texture = texture;
	sprite.color = color;

	spritesCount++;
}
void SpriteBatch::end() {
	if (!isDrawing) {
		return;
	}

	flushBatch();

	vertices.clear();

	spritesCount = 0;
}

SpriteBatch::~SpriteBatch() {
}
