#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Engine/Entity/Entity/Entity.h"
#include "../../Engine/Entity/Component/Trans/TransformComponent.h"
#include "../../Engine/Entity/Component/Render/RenderComponent.h"
#include "../../Engine/ImGui/ImGuiManager.h"
#include "../../Engine/ImGui/Editor/EditorUI/EditorUI.h"
#include "../../Engine/System/Thread/LoadedEntityQueue.h"
#include "../../Engine/Data/ObjData.h"
using namespace EngineCore;
void GameScene::Event()
{
	std::shared_ptr<Entity> entity;
	while (LoadedEntityQueue::Instance().TryPop(entity))
	{
		m_entities.push_back(entity);
		m_objList.push_back(entity);
	}
}

void GameScene::Init()
{
	auto objData = std::make_shared<ObjectData>();
	const std::string savePath = "Asset/Data/ObjData/ObjData/ObjData.json";

	if (std::filesystem::exists(savePath))
	{
		auto entityList = objData->LoadEntityList(savePath);
		m_entities = entityList;
	}
	else
	{
		EngineCore::TaskManager::Submit([]()
			{
				auto entity = std::make_shared<Entity>();

				//	コンポーネント
				entity->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());
				entity->AddComponent<RenderComponent>(std::make_shared<RenderComponent>());
				entity->Init();

				LoadedEntityQueue::Instance().Push(entity);
			});
	}
	//	エディタ
	m_editor = std::make_shared<EditorUI>();
	m_editor->SetEntityList(m_entities);
}
