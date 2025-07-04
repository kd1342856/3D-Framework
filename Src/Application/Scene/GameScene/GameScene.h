#pragma once

#include"../BaseScene/BaseScene.h"
#include"../../Engine/Entity/Entity.h"

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init()  override;

	std::vector<std::shared_ptr<Entity>> m_entities;
};
