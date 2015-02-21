#pragma once
#include <Vector.hpp>

struct VertexPositionColorTexture {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;

	VertexPositionColorTexture(const float x, const float y, const float z, const float r, const float g, const float b, const float a, const float u, const float v);
	VertexPositionColorTexture();
};
