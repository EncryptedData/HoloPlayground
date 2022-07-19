
export module Engine.Core.GameEngine;
import Engine.Core.DeltaTime;
import Engine.Core.FrameTimer;
import Engine.Core.Platform;

namespace Engine::Core
{
	export struct GameEngineCreationInfo
	{
		IPlatform* _platform;
		int _targetFps;
	};

	export class GameEngine
	{
	public:
		explicit GameEngine(const GameEngineCreationInfo& gameEngineCreationInfo);

		void Start();

	private:

		GameEngineCreationInfo _info;
		FrameTimer _timer;
		float _targetDt;

		void DoTick();

		void CallUpdateTick(const DeltaTime& dt);

		void CallFixedUpdateTick(const DeltaTime& dt);

		size_t GetNumerOfFixedSteps(float lastDt);
	};
}

module :private;

namespace Engine::Core
{
	GameEngine::GameEngine(const GameEngineCreationInfo& gameEngineCreationInfo) :
		_info{gameEngineCreationInfo},
		_timer{}
	{
		_targetDt = 1.0f / (float)_info._targetFps;
	}

	void GameEngine::Start()
	{
		while (_info._platform->ShouldContinue())
		{
			DoTick();
		}
	}

	void GameEngine::DoTick()
	{
		// First update the Platform
		_info._platform->Update();

		// Get the timing from the last loop
		DeltaTime dt{ _timer.GetLastDuration(), _targetDt, 1.0f };
		size_t fixedStepCount = GetNumerOfFixedSteps(dt.getDt());

		// Start timing
		_timer.Start();

		// Fixed Update
		for (size_t i = 0; i < fixedStepCount; i++)
		{
			CallFixedUpdateTick(dt);
		}

		// Do system update
		CallUpdateTick(dt);

		// End timing
		_timer.End();
	}

	void GameEngine::CallUpdateTick(const DeltaTime& /*dt*/)
	{
	}

	void GameEngine::CallFixedUpdateTick(const DeltaTime& /*dt*/)
	{
	}

	size_t GameEngine::GetNumerOfFixedSteps(float lastDt)
	{
		return (lastDt > _targetDt) ? (size_t)(lastDt / _targetDt) : 1;
	}
}