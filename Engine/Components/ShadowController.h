#ifndef SHADOWCONTROLLER_H
#define SHADOWCONTROLLER_H

#include "Systems/Components/Component.h"
#include "Systems/Components/ComponentsFactory.h"

#include <vector>

#include "Lighting/DirectionalLight.h"

class ShadowController : public Component
{
private:
	std::vector<DirectionalLight*> _directionalLights;

public:
	void Start ();
	
	void Update ();
};

REGISTER_COMPONENT(ShadowController)

#endif