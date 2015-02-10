#include "Color.h"
#include "Vector4.hpp"

Color::Color(float r, float g, float b, float a) : data(r, g, b, a) {
}

#pragma region Public members
float Color::r() const { return data.x; }
float Color::g() const { return data.y; }
float Color::b() const { return data.x; }
float Color::a() const { return data.w; }
#pragma endregion