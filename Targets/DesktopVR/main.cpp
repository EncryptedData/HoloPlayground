#include <engine_openxr.h>

import Engine.XR;
import Engine.Core.GameEngine;
import SDL.Platform;

int main()
{
	Engine::XR::ExtensionList extensions{};
	extensions.push_back(XR_EXT_DEBUG_UTILS_EXTENSION_NAME);
	//extensions.push_back(XR_KHR_VULKAN_ENABLE2);
	
	Engine::XR::OpenXrService openXrService{};
	SDLPlatform platform{};

	if (!platform.Initialize(1280, 720))
	{
		return -1;
	}

	if (!openXrService.Initialize(extensions))
	{
		return -2;
	}

	Engine::Core::GameEngineCreationInfo info{};
	info._platform = &platform;
	info._targetFps = 60;

	Engine::Core::GameEngine gameEngine{ info };
	gameEngine.Start();

	return 0;
}
