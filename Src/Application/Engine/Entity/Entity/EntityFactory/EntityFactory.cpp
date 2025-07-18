#include "EntityFactory.h"
#include "../Entity.h"
#include "../../Component/Trans/TransformComponent.h"
#include "../../Component/Render/RenderComponent.h"

std::shared_ptr<Entity> EntityFactory::CreatePlayer()
{
	auto entity = std::make_shared<Entity>();
	entity->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());
	entity->AddComponent<RenderComponent>(std::make_shared<RenderComponent>());
	entity->SetName("Player");
	entity->Init();
	return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateEnemy()
{
	auto entity = std::make_shared<Entity>();
	entity->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());
	entity->AddComponent<RenderComponent>(std::make_shared<RenderComponent>());
	entity->SetName("Enemy");
	return entity;
}

std::shared_ptr<Entity> EntityFactory::CreateObject()
{
	auto entity = std::make_shared<Entity>();
	entity->AddComponent<TransformComponent>(std::make_shared<TransformComponent>());
	entity->AddComponent<RenderComponent>(std::make_shared<RenderComponent>());
	entity->SetName("Object");
	return entity;
}
