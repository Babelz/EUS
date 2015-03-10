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

	const float x() const;
	const float y() const;
	const float z() const;

	void setZ(const float value);
	void setX(const float value);
	void setY(const float value);

	const float scaleX() const;
	const float scaleY() const;

	void setScale(const float value);
	void setScaleX(const float value);
	void setScaleY(const float value);

	const float originX() const;
	const float originY() const;

	void setOriginX(const float value);
	void setOriginY(const float value);

	void setSource(const pmath::Rectf& source);
	const bool isUsingSource() const;
	
	void useSource();
	void disableSource();

	const size_t textureHeight() const;
	const size_t textureWidth() const;

	const pmath::Vec4f getColor() const;
	void setColor(pmath::Vec4f& value);

	void swapTexture(Texture* const texture);

	void draw(SpriteBatch& spriteBatch);

	~Sprite();
};

