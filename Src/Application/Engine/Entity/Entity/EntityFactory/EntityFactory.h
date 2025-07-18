#pragma once
class Entity;
namespace EntityFactory
{
	std::shared_ptr<Entity> CreatePlayer();
	std::shared_ptr<Entity> CreateEnemy();
	std::shared_ptr<Entity> CreateObject();
}