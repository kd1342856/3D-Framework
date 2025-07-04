#include "GameScene.h"
#include"../SceneManager.h"
#include "../../Engine/Compornent/Entity.h"
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
	auto entity = std::make_shared<Entity>();
	entity->Init();
	m_objList.push_back(entity);
}
