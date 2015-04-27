#include "ModelRenderer.h"

ModelRenderer::ModelRenderer(Game& game, Entity& owner, Model* const model, const int updateOrder, const int drawOrder) : DrawableComponent(game, owner, updateOrder, drawOrder),
																														  model(model),
																														  vertexArray(0),
																														  vertexBuffer(0) {
	shader = game.content().load<Effect>("basic3d");

	require(model != nullptr, "ModelRenderer: model cant be null");

	textureID = model->getTexture()->getId();
}

#pragma region Private members
void ModelRenderer::releaseBuffers() {
	glDeleteBuffers(1, &vertexArray);
	glDeleteBuffers(1, &vertexBuffer);
}
void ModelRenderer::initializeBuffers() {
	// Initialize buffers.
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
	
	glBufferData(GL_ARRAY_BUFFER, model->getVertices().size() * sizeof(float), model->getVertices().data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
#pragma endregion

#pragma region Protected members
void ModelRenderer::onInitialize() {
	initializeBuffers();
}

void ModelRenderer::onDraw(const float deltaTime) {
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	shader->bind();

	glBindTexture(GL_TEXTURE_2D, textureID);

	// TODO: fix. Using static res.
	glm::mat4 projection = glm::translate(glm::vec3(-0.9f, 0.84f, 0.0f)) * glm::perspective(glm::radians(65.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
								 glm::vec3(0.0f, 0.0f, 0.0f),
								 glm::vec3(0.0f, 1.0f, 0.0f));

	GLuint mvp = glGetUniformLocation(shader->getProgram(), "MVP");
 	glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(projection * view * getOwner().getTransform().getTransform()));

	glDrawArrays(GL_TRIANGLES, 0, model->getVertices().size());

	shader->unbind();

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	assert(glGetError() == 0);
}
#pragma endregion

#pragma region Public members
void ModelRenderer::setTextureId(GLuint id) {
	textureID = id;
}
#pragma endregion

ModelRenderer::~ModelRenderer() {
	releaseBuffers();
}
