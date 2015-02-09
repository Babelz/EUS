#pragma once
#include <list>
#include <string>
#include "EntityManager.h"

class SceneManager;

class Scene {
private:
	std::string name;

	bool activated;
protected:
	SceneManager* sceneManager;
	EntityManager entities;

	SceneManager& getSceneManager() const;
	EntityManager& getEntities();

	void onActivate();
	void onResume();
public:
	Scene(const std::string& name);

	std::string& getName();
	void activate(SceneManager* const sceneManager);

	void destroy();

	virtual void draw();
	virtual void update();

	virtual ~Scene();
};

class SceneManager {
private:
	std::string empty;

	std::list<Scene* const> scenes;

	Scene* activeScene;

	bool containsScene(Scene* const scene) const;
	bool containsSceneWithName(const std::string& name) const;
	Scene* const findSceneWithName(const std::string& name) const;
public:
	SceneManager();

	std::string& currentSceneName();

	bool addScene(Scene* const scene);
	bool removeScene(Scene* const scene);
	bool freeScene(const std::string& name);

	// Changes scene and returns current scenes name.
	std::string& changeScene(const std::string& name);

	void update();
	void draw();

	~SceneManager();
};

