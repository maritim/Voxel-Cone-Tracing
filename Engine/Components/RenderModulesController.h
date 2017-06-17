#ifndef RENDERMODULESCONTROLLER_H
#define RENDERMODULESCONTROLLER_H

#include "Systems/Components/Component.h"	
#include "Systems/Components/ComponentsFactory.h"

#include "SceneNodes/TextGUI.h"

class RenderModulesController : public Component
{
private:
	SceneObject* _sun;
	SceneObject* _shadowsSun;
	SceneObject* _giSun;

	TextGUI** _textGUI;

public:
	void Start ();

	void Update ();
};

REGISTER_COMPONENT (RenderModulesController)

#endif