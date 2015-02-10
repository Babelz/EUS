#include "SceneManager.h"

#pragma region Scene class

Scene::Scene(const std::string& name) : name(name), activated(false) {
}

#pragma region Protected members
SceneManager& Scene::getSceneManager() const  {
	return *sceneManager;
}
EntityManager& Scene::getEntities() {
	return entities;
}

void Scene::onActivate() { }
void Scene::onResume() { }
#pragma endregion

#pragma region Public members
const std::string& Scene::getName() {
	return name;
}

void Scene::activate(SceneManager* const sceneManager) {
	// First call, allow user to initialize the scene.
	if (!activated) {
		activate(sceneManager);

		onActivate();

		activated = true;
	} else {
		onResume();
	}
}

void Scene::draw() { }
void Scene::update() { }
#pragma endregion

Scene::~Scene() {
}

#pragma endregion

#pragma region Scene manager class

SceneManager::SceneManager() : activeScene(nullptr) {
}

#pragma region Private members
bool SceneManager::containsScene(Scene* const scene) const {
	return std::find(scenes.begin(), scenes.end(), scene) != scenes.end();
}
bool SceneManager::containsSceneWithName(const std::string& name) const {
	Scene* result = findSceneWithName(name);

	return result != nullptr;
}
Scene* const SceneManager::findSceneWithName(const std::string& name) const {
	auto result = std::find_if(scenes.begin(), scenes.end(), [&, name](Scene* s) {
		return s->getName() == name;
	});

	return *result;
}
#pragma endregion

#pragma region Public members
bool SceneManager::addScene(Scene* const scene) {
	// Just to be sure that scenes have unique name.
	assert(!containsSceneWithName(scene->getName()));

	bool add = !containsScene(scene);

	if (add) {
		scenes.push_back(scene);
	}

	return add;
}
bool SceneManager::removeScene(Scene* const scene) {
	bool remove = containsScene(scene);

	if (remove) {
		scenes.remove(scene);
	}

	return remove;
}
bool SceneManager::freeScene(const std::string& name) {
	Scene* scene = findSceneWithName(name);

	bool freeScene = scene != nullptr;

	if (freeScene) {
		bool wasActive = activeScene == scene;
		
		scenes.remove(scene);

		delete scene;
		scene = nullptr;

		// Set active to null if needed.
		if (wasActive) {
			activeScene = nullptr;
		}
	}

	return freeScene;
}

const std::string& SceneManager::changeScene(const std::string& name) {
	Scene* scene = findSceneWithName(name);

	if (scene != nullptr) {
		Scene* last = activeScene;
		activeScene = scene;

		return activeScene->getName();
	}

	return empty;
}

void SceneManager::update() {
	if (activeScene == nullptr) {
		return;
	}

	activeScene->update();
}
void SceneManager::draw() {
	if (activeScene == nullptr) {
		return;
	}

	activeScene->draw();
}
#pragma endregion

SceneManager::~SceneManager() {
	std::for_each(scenes.begin(), scenes.end(), [](Scene* s) {
		delete s;

		s = nullptr;
	});
}

#pragma endregion
