
export module Engine.Core.Platform;

namespace Engine::Core
{
	export class IPlatform
	{
	public:

		virtual ~IPlatform() = default;

		virtual bool Update() = 0;
	};
}

