#include "Time.h"
using namespace EngineCore;

std::chrono::steady_clock::time_point Time::s_startTime;
std::chrono::steady_clock::time_point Time::s_lastFrameTime;
float Time::s_deltaTime = 0.0f;

void Time::Init()
{
	s_startTime = s_lastFrameTime = std::chrono::steady_clock::now();
}

void Time::Update()
{
	auto now = std::chrono::steady_clock::now();
	s_deltaTime = std::chrono::duration<float>(now - s_lastFrameTime).count();
	s_lastFrameTime = now;
}

float Time::DeltaTime()
{
	return s_deltaTime;
}

float Time::TimeSinceStart()
{
	return std::chrono::duration<float>(s_lastFrameTime - s_startTime).count();
}