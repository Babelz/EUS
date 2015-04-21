#ifndef RESOURCES_H
#define RESOURCES_H

#include "StringHelper.h"
#include "Vector.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <lodepng\lodepng.h>
#include <GL\glew.h>

class Resource {
public:
	Resource();

	virtual bool readFromFile(const std::string& path) = 0;

	virtual ~Resource();
};

class Texture : public Resource {
private:
	GLuint id;
public:
	size_t width;
	size_t height;
	
	Texture();

	bool readFromFile(const std::string& path);
	const GLuint& getId() const;
	
	~Texture();
};

class Effect : public Resource {
private:
	GLuint program = 0;

	std::string readFile(const std::string& path);
	GLuint compileShaders(const char* vertexSrc, const char* fragmentSrc);
public:
	Effect();

	bool readFromFile(const std::string& path);
	void bind() const;
	void unbind() const;
	GLuint getProgram() const;

	~Effect();
};

class Model : public Resource {
private:

	#pragma region Tokens
	// Material lib token.
	static const std::string MATERIAL_LIB;
	// Vertice token.
	static const std::string VERTICE;
	// Texture vertices.
	static const std::string TEXTURE_VERTICE;
	// Vertex normals.
	static const std::string VERTICE_NORMAL;
	
	// Material name token.
	static const std::string MATERIAL_NAME;
	// Smoothing grouping token.
	static const std::string SMOOTH_GROUPING;
	// Facing token.
	static const std::string FACING;

	// Comment tag, just skip them.
	static const char COMMENT;
	// Token used to split lines into tokens.
	static const std::string ATRRIB_SPLIT;
	static const std::string FACING_SPLIT;
	#pragma endregion

	std::string smoothingGroup;
	std::string materialName;

	std::vector<float> vertices;

	std::string materialLib;

	Texture* texture;
public:
	Model();

	bool readFromFile(const std::string& path);

	bool isEmpty() const;

	const std::vector<float>& getVertices() const;

	void setTexture(Texture* const texture);
	Texture* const getTexture() const;

	~Model();
};

#endif