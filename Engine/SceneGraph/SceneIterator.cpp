#include "SceneIterator.h"

SceneIterator::SceneIterator (Scene* scene, std::size_t startPos)
{
	_scene = scene;
	_currentPos = startPos;
}

SceneIterator::~SceneIterator ()
{

}

SceneIterator& SceneIterator::operator ++ ()
{
	for (++_currentPos; _currentPos < _scene->_sceneObjects.size () && 
		!_scene->_sceneObjects [_currentPos]->IsActive ();_currentPos ++);

	return *this;
}

bool SceneIterator::operator != (const SceneIterator& other)
{
	return other._scene == _scene && _currentPos != other._currentPos;
}

SceneObject* SceneIterator::operator* ()
{
	return _scene->_sceneObjects [_currentPos];
}