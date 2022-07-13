
module;

#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

export module Engine.XR;

import Engine.Core.Platform;

namespace Engine::XR
{
	export class OpenXrPlatform : 
		public Core::IPlatform
	{
	public:

		bool Initialize()
		{
			return false;
		}

		bool Update() override
		{
			return false;
		}
	};

}
