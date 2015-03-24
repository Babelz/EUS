#pragma once
#include <list>
#include <string>
#include "EntityManager.h"

class SceneManager;

class Scene {
private:
	SceneManager* sceneManager;
	EntityManager entities;
	Game* game;

	const std::string name;

	bool activated;
	bool destroyed;
protected:
	SceneManager& getSceneManager();
	Game& getGame();

	// Called at destroy.
	virtual void onDestroy();
	// Called at first activate call.
	virtual void onActivate();
	// Called when the scene resumes.
	virtual void onResume();
public:
	Scene(const std::string& name);

	const std::string& getName() const;
	void activate(Game& game, SceneManager* const sceneManager);

	void destroy();
	const bool isDestroyed() const;

	virtual void draw(const float deltaTime);
	virtual void update(const float deltaTime);

	EntityManager& getEntities();

	virtual ~Scene();
};

class SceneManager {
private:
	Game& game;

	std::string empty;

	std::list<Scene* const> scenes;

	Scene* activeScene;

	const bool containsScene(Scene* const scene) const;
	const bool containsSceneWithName(const std::string& name) const;
	Scene* const findSceneWithName(const std::string& name) const;
public:
	SceneManager(Game& game);

	const bool addScene(Scene* const scene);
	const bool removeScene(Scene* const scene);
	const bool freeScene(const std::string& name);
	
	Scene& getActiveScene() const;

	// Changes scene and returns current scenes name.
	const std::string& changeScene(const std::string& name);

	void update(const float deltaTime);
	void draw(const float deltaTime);

	~SceneManager();
};

