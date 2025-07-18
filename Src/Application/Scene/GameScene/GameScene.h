#pragma once

#include"../BaseScene/BaseScene.h"
#include"../../Engine/Entity/Entity/Entity.h"
class KdTexture;
class EditorManager;
class EditorCamera;
class GameScene : public BaseScene
{
public :
	GameScene() {}
	~GameScene() {}

	void Init()  override;
private:
	void Event() override;
	std::shared_ptr<EditorManager> m_editor;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::shared_ptr<EditorCamera>	m_camera;


};
