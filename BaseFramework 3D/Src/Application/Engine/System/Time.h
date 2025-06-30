#pragma once
namespace EngineCore
{
	class Time
	{
	public:
		static void Init();
		static void Update();
		static float DeltaTime();
		static float TimeSinceStart();

	private:
		static std::chrono::steady_clock::time_point s_startTime;
		static std::chrono::steady_clock::time_point s_lastFrameTime;
		static float s_deltaTime;
	};
}
