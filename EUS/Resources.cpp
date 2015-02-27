#include "resources.h"

#pragma region Resource class
Resource::Resource() {
}

Resource::~Resource() {
}
#pragma endregion

#pragma region Texture class
Texture::Texture() : Resource(), width(0), height(0) {
}

bool Texture::readFromFile(const std::string& path) {
	// we only accept pngs
	std::string fullpath(path + ".png");
	std::vector<unsigned char> png;

	lodepng::load_file(png, fullpath);
	std::vector<unsigned char> pixels;
	size_t error = lodepng::decode(pixels, width, height, png.data(), png.size());

	if (error) {
		std::fprintf(stderr, "Error loading texture file %s\n", lodepng_error_text(error));
		return false;
	}

	// create new name for texture
	glGenTextures(1, &id);
	// bind it so we can modify it
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	// set GL_NEAREST filter on
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
const GLuint& Texture::getId() const {
	return id;
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}
#pragma endregion

#pragma region Effect class
Effect::Effect() : program(0) {
}

#pragma region Private members
std::string Effect::readFile(const std::string& filepath) {
	std::ifstream fileStream(filepath, std::ios::binary);
	assert(fileStream.good());

	fileStream.seekg(0u, std::ios::end);
	std::string source;
	source.reserve(static_cast<unsigned int>(fileStream.tellg()));
	fileStream.seekg(0u, std::ios::beg);
	source.assign(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>());
	assert(fileStream.good());

	return source;
}
GLuint Effect::compileShaders(const char* vertexSrc, const char* fragmentSrc) {
	GLint result = GL_FALSE;
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// create vertexshader
	glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	// create fragment shader
	glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);

	GLuint program = glCreateProgram();
	assert(program != 0);
	// attach shaders
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);


	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	assert(result == GL_TRUE);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}
#pragma endregion

#pragma region Public members
bool Effect::readFromFile(const std::string& path) {
	std::string vertex(path + ".vert");
	std::string fragment(path + ".frag");
	program = compileShaders(readFile(vertex).c_str(), readFile(fragment).c_str());
	return true;
}

void Effect::bind() const {
	glUseProgram(program);
}
void Effect::unbind() const {
	glUseProgram(0);
}

GLuint Effect::getProgram() const {
	return program;
}
#pragma endregion

Effect::~Effect() {
	glDeleteProgram(program);
}
#pragma endregion

#pragma region Model class

#pragma region Tokens
// Material lib token.
const std::string Model::MATERIAL_LIB = "mtllib";
// Vertice token.
const std::string Model::VERTICE = "v";
// Texture vertices.
const std::string Model::TEXTURE_VERTICE = "vt";
// Vertex normals.
const std::string Model::VERTICE_NORMAL = "vn";

// Material name token.
const std::string Model::MATERIAL_NAME = "usemtl";
// Smoothing grouping token.
const std::string Model::SMOOTH_GROUPING = "s";
// Facing token.
const std::string Model::FACING = "f";

// Comment tag, just skip them.
const char Model::COMMENT = '#';
// Token used to split lines into tokens.
const std::string Model::ATRRIB_SPLIT = " ";
const std::string Model::FACING_SPLIT = "/";
#pragma endregion

Model::Model() : Resource() {
}

#pragma region Public members
bool Model::readFromFile(const std::string& path) {
	std::ifstream inStream(path + ".obj");

	assert(inStream.is_open());

	int meshCount = -1;

	StringHelper strHelper;
	std::stringstream ss;
	std::string line;

	std::vector<float> uvVertices;
	std::vector<float> vertexNormals;
	std::vector<float> tmpVertices;

	std::vector<unsigned short> vertexIndices;
	std::vector<unsigned short> uvIndicies;
	std::vector<unsigned short> normalIndicies;

	while (std::getline(inStream, line)) {
		// Skip empty lines and comments.
		if (line.empty()) {
			continue;
		}
		else if (line[0] == COMMENT) {
			continue;
		}

		// Split line into tokens.
		std::vector<std::string> tokens;
		strHelper.split(line, ATRRIB_SPLIT, tokens, true);

		const std::string& first = tokens[0];

		// Get material lib.
		if (first == MATERIAL_LIB) {
			materialLib = tokens[1];
		}
		// Get model name.
		else if (first == materialName) {
			materialName = tokens[1];
		}
		// Get smoothing group.
		else if (first == SMOOTH_GROUPING) {
			smoothingGroup = tokens[1];
		}
		// Parse indices.
		else if (first == FACING) {
			std::vector<unsigned int> values;

			// Split tokens.
			for (size_t i = 1; i < tokens.size(); i++) {
				std::vector<std::string> buffer;
				strHelper.split(tokens[i], FACING_SPLIT, buffer, true);

				for (size_t j = 0; j < buffer.size(); j++) {
					ss.clear();
					ss.str(buffer[j]);

					unsigned short index = 0;
					ss >> index;

					values.push_back(index);
				}
			}

			values.reserve(0);

			int offset = values.size() > 6 ? 3 : 2;
			
			for (size_t i = 0; i < values.size(); i += offset){
				// No UV.
				if (offset == 2) {
					uvIndicies.push_back(0);
					vertexIndices.push_back(values[i]);
					normalIndicies.push_back(values[i + 1]);
					
					continue;
				}

				// Has UV.
				vertexIndices.push_back(values[i]);
				uvIndicies.push_back(values[i + 1]);
				normalIndicies.push_back(values[i + 2]);
			}
		}
		// Parse texture vertices.
		else if (first == TEXTURE_VERTICE) {
			for (size_t i = 1; i < tokens.size(); i++) {
				ss.clear();
				ss.str(tokens[i]);

				float f = 0.0f;
				ss >> f;

				uvVertices.push_back(f);
			}
		}
		else if (first == VERTICE_NORMAL) {
			// Parse normals.
			for (size_t i = 1; i < tokens.size(); i++) {
				ss.clear();
				ss.str(tokens[i]);

				float f = 0.0f;
				ss >> f;

				vertexNormals.push_back(f);
			}
		}
		else if (first == VERTICE) {
			for (size_t i = 1; i < tokens.size(); i++) {
				ss.clear();
				ss.str(tokens[i]);

				float f = 0.0f;
				ss >> f;

				tmpVertices.push_back(f);
			}
		}
	}

	tmpVertices.reserve(0);
	uvVertices.reserve(0);
	vertexNormals.reserve(0);

	// | Position (3) | Texture coords (2) | Normals (3) |

	for (size_t i = 0; i < vertexIndices.size(); i++) {
		unsigned short vertexIndex = vertexIndices[i] * 3;
		
		vertices.push_back(tmpVertices[vertexIndex - 1]);
		vertices.push_back(tmpVertices[vertexIndex - 2]);
		vertices.push_back(tmpVertices[vertexIndex - 3]);
		
		unsigned short uvIndex = uvIndicies[i] * 2;
		
		// No texture coords. 
		if (uvIndex == 0) {
			for (size_t i = 0; i < 2; i++) {
				vertices.push_back(0.0f);
			}
		}  else {
			// Push texture coordinates.
			vertices.push_back(uvVertices[uvIndex - 1]);
			vertices.push_back(uvVertices[uvIndex - 2]);
		}

		unsigned short normalIndex = normalIndicies[i] * 3;
		// Push normals data.
		if (normalIndicies.size() == 0) {
			for (size_t i = 0; i < 3; i++) {
				vertices.push_back(0.0f);
			}
		}
		else {
			vertices.push_back(vertexNormals[normalIndex - 1]);
			vertices.push_back(vertexNormals[normalIndex - 2]);
			vertices.push_back(vertexNormals[normalIndex - 3]);
		}
	}

	return true;
}

bool Model::isEmpty() const {
	return vertices.size() == 0;
}

const std::vector<float>& Model::getVertices() const {
	return vertices;
}
#pragma endregion

Model::~Model() {
}
#pragma endregion
