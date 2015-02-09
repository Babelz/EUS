#include "Game.h"

Game::Game(int windowWidth, int windowHeight) : windowWidth(windowWidth), 
												windowHeight(windowHeight),
												content(ContentManager("Content")) {
	windowTitle = std::string("OpenGL");
}

#pragma region Private members
void Game::internalInitialize() {
	// Init SDL.
	int result = SDL_Init(SDL_INIT_VIDEO);
	assert(result == 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// 32-bit color channel, 8-bits per color.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	// Create window.
	window = SDL_CreateWindow(windowTitle.c_str(), 
							  SDL_WINDOWPOS_CENTERED, 
							  SDL_WINDOWPOS_CENTERED,
							  windowWidth, 
							  windowHeight, 
							  SDL_WINDOW_OPENGL);
	assert(window != nullptr);

	// Create OpenGL context.
	context = SDL_GL_CreateContext(window);
	assert(context != nullptr);

	// Init glew.
	glewExperimental = GL_TRUE;
	const GLenum glewResult = glewInit();
	glGetError();

	assert(glewResult == GLEW_OK);

	int versionMajor, versionMinor;

	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	//glOrtho(0.0f, windowWidth, windowHeight, 0.0f, -10, 10);
	
	std::cout << "OpenGL context version: " << versionMajor << "." << versionMinor << std::endl;
	
	spriteBatch = new SpriteBatch();

	running = true;
}
void Game::internalUpdate() {
	while (SDL_PollEvent(&e) == 1) {
		running = !(e.type == SDL_QUIT);

		onEvent(e);
	}

	update();
}
void Game::internalDraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw();

	// TODO: tests
	spriteBatch->draw();

	SDL_GL_SwapWindow(window);
}
#pragma endregion

#pragma region Protected members
void Game::onExit() { }

void Game::onEvent(SDL_Event& sdl_Event) { }

void Game::initialize() { }
void Game::update() { }
void Game::draw() { }
#pragma endregion

#pragma region Public members
int Game::getWindowWidth() const {
	return windowWidth;
}
int Game::getWindowHeight() const {
	return windowHeight;
}

void Game::setWindowTitle(const std::string& value) {
	windowTitle = std::string(value);
}
std::string Game::getWindowTitle() const {
	return windowTitle;
}

void Game::run() {
	if (running) {
		return;
	}

	internalInitialize();
	initialize();

	while (running) {
		internalUpdate();
		internalDraw();
	}

	exit();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::exit() {
	if (!running || exitCalled) {
		return;
	}

	exitCalled = true;
	running = false;
	
	onExit();
}
bool Game::isRunning() {
	return running;
}
#pragma endregion

Game::~Game() {
}
