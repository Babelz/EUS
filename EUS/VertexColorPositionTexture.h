#pragma once
#include <Vector.hpp>

struct VertexPositionColorTexture {
	pmath::Vec3f position;
	pmath::Vec4f color;
	pmath::Vec2f uv;

	VertexPositionColorTexture(float x, float y, float z, float r, float g, float b, float a, float u, float v);
	VertexPositionColorTexture();
};
