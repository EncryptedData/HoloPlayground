export module Engine.Systems.IEngineSystem;
import <vector>;
import Engine.Core.DeltaTime;
import Engine.Space;

namespace Engine::Systems
{
	export class IEngineSystem
	{
	public:

		virtual ~IEngineSystem() = default;

		virtual void OnUpdate(Core::DeltaTime& dt, Space::Space& space) = 0;

		virtual void OnFixedUpdate(Core::DeltaTime& dt, Space::Space& space) = 0;

		virtual void OnSpaceEntered(Space::Space& space) = 0;

		virtual void OnSpaceLeft(Space::Space& space) = 0;

	};

	export using EngineSystemsList = std::vector<IEngineSystem*>;
}
