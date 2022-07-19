
export module Engine.Core.FrameTimer;
import <chrono>;

namespace Engine::Core
{
	export class FrameTimer
	{
	public:
		explicit FrameTimer() :
			_start{},
			_end{}
		{}

		void Start()
		{
			_start = std::chrono::high_resolution_clock::now();
		}

		void End()
		{
			_end = std::chrono::high_resolution_clock::now();
		}

		float GetLastDuration() const
		{
			return 0.0f;
		}

	private:

		using tp = std::chrono::time_point<std::chrono::high_resolution_clock>;

		tp _start;
		tp _end;

	};
}
