#pragma once

#include"../BaseScene/BaseScene.h"
#include"../../Engine/Entity/Entity/Entity.h"
class KdTexture;
class EditorUI;
class GameScene : public BaseScene
{
public :
	GameScene()  { Init(); }
	~GameScene() {}

private:
	void Event() override;
	void Init()  override;
	std::shared_ptr<EditorUI> m_editor;
	std::vector<std::shared_ptr<Entity>> m_entities;

};
