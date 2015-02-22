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
			for (size_t i = 1; i < tokens.size(); i++) {
				std::vector<std::string> values;
				strHelper.split(tokens[i], FACING_SPLIT, values, true);

				for (size_t j = 0; j < values.size(); j++) {
					ss.clear();
					ss.str(values[j]);

					unsigned int k = 0;
					ss >> k;

					indices.push_back(k);
				}
			}
		}
		// Parse texture vertices.
		else if (first == TEXTURE_VERTICE) {
			for (size_t i = 1; i < tokens.size(); i++) {
				ss.clear();
				ss.str(tokens[i]);

				float f = 0.0f;
				ss >> f;

				textureVertices.push_back(f);
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
			// Parse all vertices.
			for (size_t i = 1; i < tokens.size(); i++) {
				ss.clear();
				ss.str(tokens[i]);

				float f = 0.0f;
				ss >> f;

				vertices.push_back(f);
			}
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
const std::vector<float>& Model::getTextureVertices() const {
	return textureVertices;
}
const std::vector<float>& Model::getVertexNormals() const {
	return vertexNormals;
}
const std::vector<unsigned short>& Model::getIndices() const {
	return indices;
}
#pragma endregion

Model::~Model() {
}
#pragma endregion
