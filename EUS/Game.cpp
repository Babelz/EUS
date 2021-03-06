#include "Game.h"

Game::Game(const int windowWidth, const int windowHeight, const char* windowTitle) : windowWidth(windowWidth), 
																					 windowHeight(windowHeight),
																					 m_content(ContentManager("Content")),
																					 deltaTime(0.0f),
																					 currentTime(0.0f),
																					 lastTime(0.0f),
																					 m_sceneManager(*this) {
	this->windowTitle = std::string(windowTitle);
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
	m_window = SDL_CreateWindow(windowTitle.c_str(), 
								SDL_WINDOWPOS_CENTERED, 
								SDL_WINDOWPOS_CENTERED,
								windowWidth, 
								windowHeight, 
								SDL_WINDOW_OPENGL);
	assert(m_window != nullptr);

	// Create OpenGL context.
	context = SDL_GL_CreateContext(m_window);
	assert(context != nullptr);

	// Init glew.
	glewExperimental = GL_TRUE;
	const GLenum glewResult = glewInit();
	glGetError();

	assert(glewResult == GLEW_OK);

	int versionMajor, versionMinor;

	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glGetError();

	std::cout << "OpenGL context version: " << versionMajor << "." << versionMinor << std::endl;

	//m_spriteBatch.initialize();

	running = true;
}
void Game::internalUpdate() {
	while (SDL_PollEvent(&e) == 1) {
		running = !(e.type == SDL_QUIT);

		onEvent(e);
	}

	update(deltaTime);

	SDL_Delay(16);
}
void Game::internalDraw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	draw(deltaTime);

	SDL_GL_SwapWindow(m_window);
}
#pragma endregion

#pragma region Protected members
void Game::onExit() { }

void Game::onEvent(const SDL_Event& e) { }

void Game::initialize() { }
void Game::update(float deltaTime) { }
void Game::draw(float deltaTime) { }
#pragma endregion

#pragma region Public members
ContentManager& Game::content() {
	return m_content;
}
SpriteBatch& Game::spriteBatch() {
	return m_spriteBatch;
}
SceneManager& Game::sceneManager() {
	return m_sceneManager;
}
InputManager& Game::inputManager() {
	return m_inputManager;
}
SDL_Window& Game::window() {
	return *m_window;
}

View& Game::view() {
	return m_view;
}

const int Game::getWindowWidth() const {
	return windowWidth;
}
const int Game::getWindowHeight() const {
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
		currentTime = static_cast<float>(SDL_GetTicks());
		deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		m_inputManager.update();

		internalUpdate();
		internalDraw();
	}

	exit();

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(m_window);

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
const bool Game::isRunning() {
	return running;
}
#pragma endregion

Game::~Game() {
}
