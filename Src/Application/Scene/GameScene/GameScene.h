#pragma once

#include"../BaseScene/BaseScene.h"
#include"../../Engine/Entity/Entity/Entity.h"
class KdTexture;
class EditorManager;
class GameScene : public BaseScene
{
public :
	GameScene()  {}
	~GameScene() {}

private:
	void Event() override;
	void Init()  override;
	std::shared_ptr<EditorManager> m_editor;
	std::vector<std::shared_ptr<Entity>> m_entities;

};
