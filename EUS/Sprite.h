#pragma once
#include "Require.h"
#include "Vector4.hpp"
#include "Resources.h"
#include "SpriteBatch.h"

class Sprite {
private:
	pmath::Vec3f position;
	pmath::Vec2f scale;
	pmath::Vec2f origin;
	pmath::Vec4f color;
	pmath::Rectf source;

	Texture* texture;
	bool usingSource;
public:
	Sprite(Texture* const texture);
	Sprite();

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

	void setSource(const pmath::Rectf& source);
	bool isUsingSource() const;
	
	void useSource();
	void disableSource();

	size_t textureHeight() const;
	size_t textureWidth() const;

	pmath::Vec4f getColor() const;
	void setColor(pmath::Vec4f& value);

	void swapTexture(Texture* const texture);

	void draw(SpriteBatch& spriteBatch);

	~Sprite();
};

