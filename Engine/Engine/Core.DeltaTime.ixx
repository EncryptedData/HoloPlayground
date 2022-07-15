export module Engine.Core:DeltaTime;

namespace Engine::Core
{
	class DeltaTime
	{
	public:
		explicit DeltaTime(float dt, float fixedDt, float dtMod = 1.0f) :
			_dt{dt},
			_fixedDt{fixedDt},
			_dtMod{dtMod}
		{}

		/// <summary>
		/// The dt for use in Update()
		/// </summary>
		/// <returns>The current Dt</returns>
		float getDt() const
		{
			return _dt * _dtMod;
		}

		/// <summary>
		/// Gets the unmodified Dt for use in Update()
		/// </summary>
		/// <returns>The unmodified Dt</returns>
		float getRealDt() const
		{
			return _dt;
		}

		/// <summary>
		/// Gets the Dt for use in FixedUpdate()
		/// </summary>
		/// <returns>The fixed update dt</returns>
		float getFixedDt() const
		{
			return _fixedDt;
		}

	private:
		float _dt;
		float _fixedDt;
		float _dtMod;
	};
}