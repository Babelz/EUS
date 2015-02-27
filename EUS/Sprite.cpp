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

void Sprite::setSource(const pmath::Rectf& source) {
	this->source = source;
}
bool Sprite::isUsingSource() const {
	return usingSource;
}

void Sprite::useSource() {
	usingSource = true;
}
void Sprite::disableSource() {
	usingSource = false;
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
	require(texture != nullptr, "Sprite: texture cant be null");

	this->texture = texture;
}

void Sprite::draw(SpriteBatch& spriteBatch) {
	require(texture != nullptr, "Sprite: texture cant be null");

	if (usingSource) {
		pmath::Rectf destination(position.x,
			position.y, 32, 32);
								 //source.size.x * scale.x, 
								 //source.size.y * scale.y);

		spriteBatch.draw(texture, source, destination, color);

		return;
	}

	spriteBatch.draw(texture, position, origin, color, scale.x, scale.y);
}
#pragma endregion

Sprite::~Sprite() {
}