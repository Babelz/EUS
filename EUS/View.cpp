#include "View.h"

View::View() : x(0.f), y(0.f) {
}

#pragma region Public members
float View::getX() const {
	return x;
}
float View::getY() const{
	return y;
}

void View::setX(float x) {
	this->x = x;
}
void View::setY(float y) {
	this->y = y;
}

float View::getRotX() const {
	return rotX;
}
float View::getRotY() const{
	return rotY;
}

void View::setRotX(float x) {
	this->rotX = x;
}
void View::setRotY(float y) {
	this->rotY = y;
}
#pragma endregion

View::~View() {
}
