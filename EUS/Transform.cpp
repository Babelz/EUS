#include "Transform.h"

Transform::Transform() : transform(1.0f),
						 scale(1.0f),
						 rotation(1.0f) {
}

#pragma region Public members
void Transform::setPosition(const Vector3& position) {
	this->position = position;

	transform = glm::translate(position);
}
void Transform::setX(const float x) {
	setPosition(Vector3(x, position.y, position.z));
}
void Transform::setY(const float y) {
	setPosition(Vector3(position.x, y, position.z));
}
void Transform::setZ(const float z) {
	setPosition(Vector3(position.x, position.y, z));
}

Vector3 Transform::getPosition() const {
	return position;
}

void Transform::setRotation(const float r, const Vector3& axis) {
	rotation = glm::rotate(r, axis);
}
Matrix4 Transform::getRotation() const {
	return rotation;
}

void Transform::lookAt(const Vector3& vector) {
	Vector3 delta = position - vector;
	Vector3 axis(0.0f, 0.0f, 1.0f);

	float angle = glm::atan(delta.x, delta.y);

	rotation = glm::rotate(angle, axis);
}
void Transform::translate(const Vector3& vector) {
	transform = glm::translate(transform, vector);
	position += vector;
}

Matrix4 Transform::getTransform() const {
	return transform * rotation * scale;
}

void Transform::setScale(const float value) {
	scale = Matrix4(value);
}
#pragma endregion

Transform::~Transform() {
}
