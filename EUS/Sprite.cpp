#include "Sprite.h"

Sprite::Sprite(Texture* texture) : color(1.0f),
								   scale(1.0f), 
								   texture(texture) {
	assert(texture != nullptr);
}
Sprite::Sprite() : color(1.0f),
				   scale(1.0f),
				   texture(texture) {
}

#pragma region Public members
float Sprite::x() const {
	return position.x;
}
float Sprite::y() const {
	return position.y;
}

void Sprite::setX(float value) {
	position.x = value;
}
void Sprite::setY(float value) {
	position.y = value;
}

float Sprite::scaleX() const {
	return scale.x;
}
float Sprite::scaleY() const {
	return scale.y;
}

void Sprite::setScale(float value) {
	scale.x = value;
	scale.y = value;
}
void Sprite::setScaleX(float value) {
	scale.x = value;
}
void Sprite::setScaleY(float value) {
	scale.y = value;
}

float Sprite::originX() const {
	return origin.x;
}
float Sprite::originY() const {
	return origin.y;
}

void Sprite::setOriginX(float value) {
	origin.x = value;
}
void Sprite::setOriginY(float value) {
	origin.y = value;
}

size_t Sprite::textureHeight() const {
	return texture->height;
}
size_t Sprite::textureWidth() const {
	return texture->width;
}

pmath::Vec4f Sprite::getColor() const {
	return color;
}
void Sprite::setColor(pmath::Vec4f& value){
	color = value;
}

void Sprite::swapTexture(Texture* const texture) {
	assert(texture != nullptr);

	this->texture = texture;
}

void Sprite::draw(SpriteBatch& spriteBatch) {
	assert(texture != nullptr);

	spriteBatch.draw(texture, position, origin, color, scale.x, scale.y);
}
#pragma endregion

Sprite::~Sprite() {
}