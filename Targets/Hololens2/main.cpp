
#include <Windows.h>

import Engine.XR;

int __stdcall wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	Engine::XR::OpenXrPlatform platform{};

	if (!platform.Initialize())
	{
		return -1;
	}

	return 0;
}
