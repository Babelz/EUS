#ifndef RESOURCES_H
#define RESOURCES_H

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

#endif