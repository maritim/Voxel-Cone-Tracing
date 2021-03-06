#include "SceneManager.h"

#include "Resources/SceneLoader.h"

#include "Core/Console/Console.h"

#define SCENE_LOADING_ERROR_CODE 10

SceneManager::SceneManager () :
	_current (nullptr)
{

}

SceneManager::~SceneManager ()
{
	Clear ();
}

Scene* SceneManager::Current ()
{
	return _current;
}

/*
 * TODO: Improve this to manage more cleaning stuff
*/

Scene* SceneManager::Load (const std::string& sceneName)
{
	Clear ();

	_current = SceneLoader::Instance ().Load (sceneName);

	if (_current == nullptr) {
		Console::LogError ("An error occured while tryng to load " + sceneName);
		std::exit(SCENE_LOADING_ERROR_CODE);
	}

	/*
	 * Initialization of scene (need cleanup of last scene)
	*/

	_current->Init ();

	return _current;
}

void SceneManager::Clear ()
{
	if (_current == nullptr) {
		return ;
	}

	delete _current;
	_current = nullptr;
}