#include "RenderModulesController.h"

#include "Core/Math/glm/vec3.hpp"
#include "Core/Math/glm/detail/func_geometric.hpp"

#include "Systems/Camera/Camera.h"
#include "Systems/Input/Input.h"
#include "Systems/Time/Time.h"

#include "Managers/SceneManager.h"
#include "Resources/Resources.h"

#include "Utils/Extensions/MathExtend.h"

#include "Renderer/RenderManager.h"

#include "Settings/GeneralSettings.h"

void RenderModulesController::Start ()
{
	_sun = SceneManager::Instance ()->Current ()->GetObject ("Sun");
	_shadowsSun = SceneManager::Instance ()->Current ()->GetObject ("ShadowsSun");
	_giSun = SceneManager::Instance ()->Current ()->GetObject ("ConeTracingSun");

	_shadowsSun->SetActive (false);
	_giSun->SetActive (false);

	GeneralSettings::Instance ()->SetIntValue ("RadianceInjection", 1);
	GeneralSettings::Instance ()->SetIntValue ("VoxelVolumeMipmapLevel", 0);
	GeneralSettings::Instance ()->SetIntValue ("ContinousVoxelizationPass", 1);

	Font* font = Resources::LoadBitmapFont ("Assets/Fonts/Fonts/sans.fnt");

	_textGUI = new TextGUI* [3];

	for (std::size_t index = 0; index < 3; index++) {
		_textGUI [index] = new TextGUI ("", font, glm::vec2 (0.0f, 0.0f + index * 0.05f));
		_textGUI [index]->GetTransform ()->SetScale (glm::vec3 (0.7f , 0.7f, 0.0f));
		SceneManager::Instance ()->Current ()->AttachObject (_textGUI [index]);
	}
}

void RenderModulesController::Update ()
{
	/*
	 * Check NotShadows/Shadows rendering mode
	*/

	if (Input::GetKeyDown (InputKey::X)) {
		if (_sun->IsActive ()) {
			_sun->SetActive (false); _shadowsSun->SetActive (true);
		}
		else if (_shadowsSun->IsActive ()) {
			_sun->SetActive (true); _shadowsSun->SetActive (false);
		}
	}

	/*
	 * Check Deferred/VoxelRayTrace render module switch
	*/

	if (Input::GetKeyDown (InputKey::Q)) {
		if (RenderManager::Instance ()->GetRenderMode () == RenderMode::RENDER_MODE_DEFERRED) {
			RenderManager::Instance ()->SetRenderMode (RenderMode::RENDER_MODE_VOXELIZATION);
		}
		else if (RenderManager::Instance ()->GetRenderMode () == RenderMode::RENDER_MODE_VOXELIZATION) {
			RenderManager::Instance ()->SetRenderMode (RenderMode::RENDER_MODE_DEFERRED);
		}
	}

	/*
	 * Check Deferred/GI render module switch
	*/

	if (Input::GetKeyDown (InputKey::E)) {
		if (RenderManager::Instance ()->GetRenderMode () == RenderMode::RENDER_MODE_DEFERRED) {
			RenderManager::Instance ()->SetRenderMode (RenderMode::RENDER_MODE_VOXEL_CONE_TRACE);
			_shadowsSun->SetActive (false); _giSun->SetActive (true);
		}
		else if (RenderManager::Instance ()->GetRenderMode () == RenderMode::RENDER_MODE_VOXEL_CONE_TRACE) {
			RenderManager::Instance ()->SetRenderMode (RenderMode::RENDER_MODE_DEFERRED);
			_shadowsSun->SetActive (true); _giSun->SetActive (false);
		}
	}

	/*
	 * Change Voxel volume Mipmap to draw on Voxelization render module
	*/

	if (RenderManager::Instance ()->GetRenderMode () == RenderMode::RENDER_MODE_VOXELIZATION) {
		int modifier = 0;

		if (Input::GetKeyDown (InputKey::PAGEDOWN)) {
			modifier = -1;
		}
		else if (Input::GetKeyDown (InputKey::PAGEUP)) {
			modifier = 1;
		}

		if (modifier != 0) {
			const int maxMipmapLevel = 6;

			int currentMipmapLevel = GeneralSettings::Instance ()->GetIntValue ("VoxelVolumeMipmapLevel");
			int nextMipmapLevel = Extensions::MathExtend::Clamp (currentMipmapLevel + modifier, 0, maxMipmapLevel);

			GeneralSettings::Instance ()->SetIntValue ("VoxelVolumeMipmapLevel", nextMipmapLevel);
		}
	}

	/*
	 * Change radiance injection settings
	*/

	if (Input::GetKeyDown (InputKey::C)) {
		int currentRadianceInjection = GeneralSettings::Instance ()->GetIntValue ("RadianceInjection");
		int nextRadianceInjection = !currentRadianceInjection;

		GeneralSettings::Instance ()->SetIntValue ("RadianceInjection", nextRadianceInjection);
	}

	/*
	 * Realtime voxel volume generation
	*/

	if (Input::GetKeyDown (InputKey::Z)) {
		int currentContinousVoxelization = GeneralSettings::Instance ()->GetIntValue ("ContinousVoxelizationPass");
		int nextContinousVoxelization = !currentContinousVoxelization;

		GeneralSettings::Instance ()->SetIntValue ("ContinousVoxelizationPass", nextContinousVoxelization);
	}

	std::string renderModule;

	switch (RenderManager::Instance ()->GetRenderMode ()) 
	{
		case RenderMode::RENDER_MODE_DEFERRED :
			renderModule = " Deferred";
			break;
		case RenderMode::RENDER_MODE_VOXELIZATION :
			renderModule = " Voxel Ray Tracing";
			break;
		case RenderMode::RENDER_MODE_VOXEL_CONE_TRACE :
			renderModule = " Global Illumination";
			break;
	}

	std::string voxelRadianceInjection = GeneralSettings::Instance ()->GetIntValue ("RadianceInjection") == 1 ? "ON" : " OFF";
	std::string continouseVoxelizationPass = GeneralSettings::Instance ()->GetIntValue ("ContinousVoxelizationPass") == 1 ? "ON" : "OFF";

	static bool activateText = false;

	if (Input::GetKeyDown (InputKey::T)) {
		activateText = !activateText;
	}

	if (activateText) {
		_textGUI [0]->SetText ("Render Module: " + renderModule);
		_textGUI [1]->SetText ("Voxel Radiance Injection: " + voxelRadianceInjection);
		_textGUI [2]->SetText ("Continous Voxelization: " + continouseVoxelizationPass);
	} else {
		for (std::size_t index = 0; index < 3; index++) {
			_textGUI [index]->SetText ("");
		}
	}
}