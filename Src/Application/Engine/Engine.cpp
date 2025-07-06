#include "Engine.h"
#include "ImGui/ImGuiManager.h"
#include <DirectXColors.h>
using namespace EngineCore;

bool Engine::Init()
{
	Logger::Log("Engine", "Engine initialized.");
	TaskManager::Init();


	m_gameViewRT = std::make_shared<KdTexture>();
	m_gameViewRT->CreateRenderTarget(1280, 720);
	return true;
}

void Engine::Shutdown()
{
	Logger::Log("Engine", "Engine shutdown");
}

void Engine::Update()
{
	//Logger::Log("Engine", "Engine update.");
}

void Engine::Draw()
{
	auto rtv = m_gameViewRT->WorkRTView();
	auto dsv = KdDirect3D::Instance().WorkZBuffer()->WorkDSView();

	KdDirect3D::Instance().SetRenderTarget(rtv, dsv);
	KdDirect3D::Instance().ClearRenderTarget(rtv, DirectX::Colors::CornflowerBlue);
	KdDirect3D::Instance().ClearDepthStencil(dsv);
}

void EngineCore::Engine::Release()
{
	TaskManager::Shutdown(TaskManager::ShutdownMode::Graceful);
}
