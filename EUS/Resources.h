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

struct ModelMesh {
public:
	std::string name;

	std::string smoothingGroup;
	std::string materialName;

	std::vector<float> vertices;
	std::vector<float> textureVertices;
	std::vector<float> vertexNormals;

	std::vector<unsigned short> indices;

	ModelMesh() {
	}

	~ModelMesh() {
	}
};

class Model : public Resource {
private:
	// Material lib token.
	const std::string MTLLIB = "mtllib";
	// Vertice token.
	const std::string VERTICE = "v";
	// Texture vertices.
	const std::string TEXTURE_VERTICES = "vt";
	// Vertex normals.
	const std::string VERTEX_NORMALS = "vn";
	
	// Material name token.
	const std::string MTNAME = "usemtl";
	// Smoothing grouping token.
	const std::string SMOOTHGRP = "s";
	// Facing token.
	const std::string FACING = "f";
	// Object name.
	const std::string OBJECTNAME = "o";

	// Comment tag, just skip them.
	const char COMMENT = '#';
	// Token used to split lines into tokens.
	const std::string SPLIT = " ";

	std::vector<ModelMesh> meshes;
	std::string materialLib;
public:
	Model();

	bool readFromFile(const std::string& path);

	bool empty() const;

	~Model();

	Model operator = (const Model& model) {
		return model;
	}
};

#endif