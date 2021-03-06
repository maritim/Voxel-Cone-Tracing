#include "PointLightRenderer.h"

#include "Managers/ShaderManager.h"

#include "PointLight.h"

PointLightRenderer::PointLightRenderer (Light* light) :
	LightRenderer (light)
{
	_shaderName = "POINT_LIGHT";

	ShaderManager::Instance ()->AddShader (_shaderName,
		"Assets/Shaders/deferredPointVolLightVertex.glsl",
		"Assets/Shaders/deferredPointVolLightFragment.glsl");
}

std::vector<PipelineAttribute> PointLightRenderer::GetCustomAttributes ()
{
	std::vector<PipelineAttribute> attributes = LightRenderer::GetCustomAttributes ();

	PipelineAttribute attenuation;

	attenuation.type = PipelineAttribute::AttrType::ATTR_3F;

	attenuation.name = "attenuationComp";

	PointLight* pointLight = dynamic_cast<PointLight*> (_light);

	attenuation.value = glm::vec3 (
		pointLight->GetConstantAttenuation (),
		pointLight->GetLinearAttenuation (),
		pointLight->GetQuadraticAttenuation ());

	attributes.push_back (attenuation);

	return attributes;
} 