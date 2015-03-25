#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator(Game& game, Entity& entity) : DrawableComponent(game, entity),
															 spriteBatch(game.spriteBatch()),
															 texture(nullptr),
															 elapsed(0.0f),
															 currentFrameIndexX(0.0f),
															 currentFrameIndexY(0.0f) {
}

#pragma region Private members
AnimationInformation& SpriteAnimator::findInformationWithName(const std::string& name) const {
	return std::find_if(animations.begin(), animations.end(), [&name](const AnimationInformation a) {
		return a.name == name;
	})._Ptr->_Myval;
}
const bool SpriteAnimator::canAnimate() const {
	return currentAnimation.empty() && texture != nullptr;
}
void SpriteAnimator::updateSource() {
	assert(canAnimate());

	source.position.x = currentFrameIndexX * size.x;
	source.position.y = currentFrameIndexY * size.y;
}
#pragma region

#pragma region Protected members
void SpriteAnimator::onUpdate(const float deltaTime) {
	if (!canAnimate()) return;

	elapsed += deltaTime;

	if (elapsed >= currentAnimation.seconds) {
		if (currentFrameIndexX + 1.0f < currentAnimation.frames) {
			// Next frame.

			currentFrameIndexX += 1.0f;
		} else {
			// Reset animation.
			
			currentFrameIndexX = currentAnimation.indexX;
		}

		updateSource();

		elapsed = 0;
	}
}
void SpriteAnimator::onDraw(const float deltaTime) {
	if (!canAnimate()) return;

	pmath::Rectf destination;

	destination.position.x = getOwner().getTransform().getPosition().x;
	destination.position.y = getOwner().getTransform().getPosition().y;

	destination.size.x = size.x;
	destination.size.y = size.y;

	spriteBatch.draw(texture, source, destination, pmath::Vec4f(1.0f));
}
#pragma endregion

#pragma region Public members
void SpriteAnimator::setTexture(Texture* const texture) {
	this->texture = texture;
}

void SpriteAnimator::createAnimation(const std::string& name, const size_t indexX, const size_t indexY) {
	assert(!containsAnimation(name));

	AnimationInformation animation;
	animation.name = name;
	animation.indexX = static_cast<float>(indexX);
	animation.indexY = static_cast<float>(indexY);

	animations.push_back(animation);
}
void SpriteAnimator::setAnimationFramesCount(const std::string& name, const size_t frames) {
	assert(containsAnimation(name));

	AnimationInformation& animation = findInformationWithName(name);
	
	animation.frames = static_cast<float>(frames);
}
void SpriteAnimator::setAnimationDuration(const std::string& name, const float seconds) {
	assert(containsAnimation(name));

	AnimationInformation& animation = findInformationWithName(name);

	animation.seconds = seconds;
}


void SpriteAnimator::setFrameSize(const size_t size) {
	const float value = static_cast<float>(size);

	source.size.x = value;
	source.size.y = value;
}
void SpriteAnimator::setAnimatorSize(const pmath::Vec2f& size) {
	this->size = size;
}

const std::string& SpriteAnimator::getCurrentAnimationName() const {
	return currentAnimation.name;
}
const bool SpriteAnimator::changeAnimation(const std::string& name) {
	if (!containsAnimation(name)) return false;

	currentAnimation = findInformationWithName(name);

	// Reset frame indices. 
	currentFrameIndexX = currentAnimation.indexX;
	currentFrameIndexY = currentAnimation.indexY;

	return true;
}
const bool SpriteAnimator::isAnimating() const {
	return canAnimate();
}

const bool SpriteAnimator::containsAnimation(const std::string& name) const {
	for (auto animation : animations) {
		if (animation.name == name) {
			return true;
		}
	}

	return false;
}

const bool SpriteAnimator::stopAnimating() {
	if (!isAnimating()) return false;

	// Set current animation to empty (default).
	currentAnimation = AnimationInformation();

	return true;
}
#pragma endregion


SpriteAnimator::~SpriteAnimator() {
}
