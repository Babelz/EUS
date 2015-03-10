#include "Sprite.h"

Sprite::Sprite(Texture* texture) : color(1.0f),
								   scale(1.0f), 
								   texture(texture) {
}
Sprite::Sprite() : color(1.0f),
				   scale(1.0f),
				   texture(nullptr) {
}

#pragma region Public members
const float Sprite::x() const {
	return position.x;
}
const float Sprite::y() const {
	return position.y;
}
const float Sprite::z() const {
	return position.z;
}

void Sprite::setZ(const float value) {
	position.z = value;
}
void Sprite::setX(const float value) {
	position.x = value;
}
void Sprite::setY(const float value) {
	position.y = value;
}

const float Sprite::scaleX() const {
	return scale.x;
}
const float Sprite::scaleY() const {
	return scale.y;
}

void Sprite::setScale(const float value) {
	scale.x = value;
	scale.y = value;
}
void Sprite::setScaleX(const float value) {
	scale.x = value;
}
void Sprite::setScaleY(const float value) {
	scale.y = value;
}

const float Sprite::originX() const {
	return origin.x;
}
const float Sprite::originY() const {
	return origin.y;
}

void Sprite::setOriginX(const float value) {
	origin.x = value;
}
void Sprite::setOriginY(const float value) {
	origin.y = value;
}

void Sprite::setSource(const pmath::Rectf& source) {
	this->source = source;
}
const bool Sprite::isUsingSource() const {
	return usingSource;
}

void Sprite::useSource() {
	usingSource = true;
}
void Sprite::disableSource() {
	usingSource = false;
}

const size_t Sprite::textureHeight() const {
	return texture->height;
}
const size_t Sprite::textureWidth() const {
	return texture->width;
}

const pmath::Vec4f Sprite::getColor() const {
	return color;
}
void Sprite::setColor(pmath::Vec4f& value){
	color = value;
}

void Sprite::swapTexture(Texture* const texture) {
	require(texture != nullptr, "Sprite: texture cant be null");

	this->texture = texture;
}

void Sprite::draw(SpriteBatch& spriteBatch) {
	require(texture != nullptr, "Sprite: texture cant be null");

	if (usingSource) {
		pmath::Rectf destination(position.x,
								 position.y, 
								 source.size.x * scale.x, 
								 source.size.y * scale.y);

		spriteBatch.draw(texture, source, destination, color);

		return;
	}

	spriteBatch.draw(texture, position, origin, color, scale.x, scale.y);
}
#pragma endregion

Sprite::~Sprite() {
}