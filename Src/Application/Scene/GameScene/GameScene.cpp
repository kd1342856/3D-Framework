#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Engine/Entity/Entity/Entity.h"
#include "../../Engine/Entity/Component/Trans/TransformComponent.h"
#include "../../Engine/Entity/Component/Render/RenderComponent.h"
#include "../../Engine/Entity/Entity/EntityFactory/EntityFactory.h"
#include "../../Engine/ImGui/Editor/EditorCamera/EditorCamera.h"
#include "../../Engine/ImGui/Editor/EditorManager.h"
#include "../../Engine/ImGui/ImGuiManager.h"
#include "../../Engine/Data/ObjData.h"
#include "../../Engine/System/Thread/LoadedEntityQueue.h"
using namespace EngineCore;
using namespace EntityFactory;
void GameScene::Event()
{
	std::shared_ptr<Entity> entity;
	while (LoadedEntityQueue::Instance().TryPop(entity))
	{
		m_entities.push_back(entity);
		m_objList.push_back(entity);
	}

	if (m_editor)
	{
		m_editor->SetEntityList(m_entities);
	}
}

void GameScene::Init()
{
	EngineCore::TaskManager::Submit([]()
		{
			auto entity = std::make_shared<Entity>();
			auto player = EntityFactory::CreatePlayer();

			//	コンポーネント
			entity->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());
			entity->AddComponent<RenderComponent>(std::make_shared<RenderComponent>());
			entity->Init();

			LoadedEntityQueue::Instance().Push(player);
			LoadedEntityQueue::Instance().Push(entity);
		});
	//	エディタ
	m_editor = std::make_shared<EditorManager>();
	m_editor->Init();	

	m_camera = std::make_shared<EditorCamera>();
	m_camera->Init();
	m_objList.push_back(m_camera);
}
