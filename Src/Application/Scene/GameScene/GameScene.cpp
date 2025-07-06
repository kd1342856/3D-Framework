#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Engine/Entity/Entity.h"
#include "../../Engine/Entity/Component/Trans/TransformComponent.h"
#include "../../Engine/Entity/Component/Render/RenderComponent.h"
#include "../../Engine/ImGui/ImGuiManager.h"
using namespace EngineCore;
void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	//TaskManager::Submit([]
	//	{
	//		Logger::Log("Async", "Load");
	//		std::this_thread::sleep_for(std::chrono::seconds(1)); 
	//		Logger::Log("Async", "End");
	//	});
	auto player = std::make_shared<Entity>();
	player->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());

	auto render = std::make_shared<RenderComponent>();
	//render->SetModel(std::make_shared<KdModelData>(""));
	//player->AddComponent<RenderComponent>(render);
	//player->GetComponent<TransformComponent>().SetPos(Math::Vector3(0, 0, 0));
	
	m_entities.push_back(player);
	ImGuiManager::Instance().SetEntityList(&m_entities);
	auto entity = std::make_shared<Entity>();
	entity->Init();
	m_objList.push_back(entity);
}
