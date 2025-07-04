#include "Engine.h"
#include "System/Time.h"
#include "System/TaskManager.h"
#include "System/Logger.h"
using namespace EngineCore;

bool Engine::Init()
{
	Logger::Log("Engine", "Engine initialized.");
	TaskManager::Init();
	return true;
}

void Engine::Shutdown()
{
	Logger::Log("Engine", "Engine shutdown");
}

void Engine::Update()
{
	Logger::Log("Engine", "Engine update.");
}

void Engine::Draw()
{
}

void EngineCore::Engine::Release()
{
	TaskManager::Shutdown(TaskManager::ShutdownMode::Graceful);
}
