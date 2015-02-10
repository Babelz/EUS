#pragma once
#include "Matrix2.hpp"
#include "Vector4.hpp"
#include "Resources.h"
#include "SpriteBatch.h"

class Sprite {
private:
	pmath::Vec3f position;
	pmath::Vec2f scale;
	pmath::Vec2f origin;
	pmath::Vec4f color;

	Texture* texture;
public:
	Sprite(Texture* texture);

	float x() const;
	float y() const;

	void setX(float value);
	void setY(float value);

	float scaleX() const;
	float scaleY() const;

	void setScale(float value);
	void setScaleX(float value);
	void setScaleY(float value);

	float originX() const;
	float originY() const;

	void setOriginX(float value);
	void setOriginY(float value);

	pmath::Vec4f getColor() const;
	void setColor(pmath::Vec4f& value);

	void swapTexture(Texture* texture);

	void draw(SpriteBatch& spriteBatch);

	~Sprite();
};

