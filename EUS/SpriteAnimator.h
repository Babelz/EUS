#pragma once
#include "Game.h"
#include "Resources.h"
#include "Rectangle.hpp"
#include "SpriteBatch.h"

struct AnimationInformation {
	std::string name;

	float frames;
	float indexX;
	float indexY;

	float millis;

	AnimationInformation() {
		frames = indexX = indexY = 0;
		millis = 0.0f;
	}

	const bool empty() const {
		return !name.empty();
	}
};

class SpriteAnimator : public DrawableComponent {
private:
	std::list<AnimationInformation> animations;
	AnimationInformation currentAnimation;

	SpriteBatch& spriteBatch;
	Texture* texture;

	pmath::Rectf source;
	pmath::Vec2f size;

	float currentFrameIndexX;
	float currentFrameIndexY;

	float elapsed;

	AnimationInformation& findInformationWithName(const std::string& name) const;
	const bool canAnimate() const;
	void updateSource();
protected:
	void onUpdate(const float deltaTime) override;
	void onDraw(const float deltaTime) override;
public:
	SpriteAnimator(Game& game, Entity& entity);
	
	// Sets sprite sheet.
	void setTexture(Texture* const texture);
	
	void createAnimation(const std::string& name, const size_t indexX, const size_t indexY);
	void setAnimationFramesCount(const std::string& name, const size_t frames);
	void setAnimationDuration(const std::string& name, const float millis);
	
	void setAnimatorSize(const pmath::Vec2f& size);

	// Returns current animations name.
	const std::string& getCurrentAnimationName() const;
	// Changes animation. Returns true if animation was changed.
	const bool changeAnimation(const std::string& name);
	// Returns true if animator is playing an animation.
	const bool isAnimating() const;
	// Returns true if animator contains animation with given name.
	const bool containsAnimation(const std::string& name) const;

	const bool stopAnimating();

	~SpriteAnimator();
};

