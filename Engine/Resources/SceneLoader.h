#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <string>

#include "Core/Parsers/XML/TinyXml/tinyxml.h"

#include "Core/Math/Vector3.h"
#include "Utils/Color/Color.h"

#include "SceneGraph/Scene.h"
#include "SceneGraph/Transform.h"

class SceneLoader
{
public:
	static SceneLoader& Instance ();

	Scene* Load (const std::string& filename);
private:
	SceneLoader ();

	void ProcessLight (TiXmlElement* xmlElem, Scene* scene);
	void ProcessSkybox (TiXmlElement* xmlElem, Scene* scene);
	void ProcessGameObject (TiXmlElement* xmlElem, Scene* scene);
	void ProcessParticleSystem (TiXmlElement* xmlElem, Scene* scene);

	void ProcessTransform (TiXmlElement* xmlElem, Scene* scene, SceneObject* obj);
	Vector3 GetPosition (TiXmlElement* xmlElem);
	Vector3 GetRotation (TiXmlElement* xmlElem);
	Vector3 GetScale (TiXmlElement* xmlElem);

	void ProcessRigidbody (TiXmlElement* xmlElem, SceneObject* object);

	void ProcessGravity (TiXmlElement* xmlElem, Rigidbody* rigidbody);
};

#endif