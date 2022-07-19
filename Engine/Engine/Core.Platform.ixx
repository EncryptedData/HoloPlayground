
export module Engine.Core.Platform;

namespace Engine::Core
{
	export class IPlatform
	{
	public:

		virtual ~IPlatform() = default;

		virtual void Update() = 0;

		virtual bool ShouldContinue() = 0;
	};
}

