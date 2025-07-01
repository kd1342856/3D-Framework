#include "Entity.h"
#include "Component.h"

void Entity::Update()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Update();
	}
}

void Entity::Draw()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw();
	}
}

void Entity::AddComponent(std::shared_ptr<Component> comp)
{
	comp->SetOwner(shared_from_this());
	m_components[typeid(*comp)] = comp;
}

