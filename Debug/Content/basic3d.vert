#version 330

layout(location = 0)
in vec3 inPosition;

layout(location = 1)
in vec2 coords;

layout(location = 2)
in vec3 normals;

out vec2 texCoords;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4(inPosition, 1.0);
	texCoords = coords;
}