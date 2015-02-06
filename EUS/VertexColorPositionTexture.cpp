#include "VertexColorPositionTexture.h"

VertexPositionColorTexture::VertexPositionColorTexture(float x, float y, float z, float r, float g, float b, float a, float u, float v)
	: position(x, y, z), color(r, g, b, a), uv(u, v) {
}

VertexPositionColorTexture::VertexPositionColorTexture() {
}