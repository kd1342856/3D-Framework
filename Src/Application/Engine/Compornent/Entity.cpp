#include "Entity.h"
#include "Component.h"

void Entity::Init()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Init();
	}
}

void Entity::Update()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Update();
	}
}

void Entity::DrawLit()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Lit);
	}
}

void Entity::DrawUnLit()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::UnLit);
	}
}

void Entity::DrawEffect()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Effect);
	}
}

void Entity::DrawBright()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Bright);
	}
}

void Entity::GenerateDepthMapFromLight()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Shadow);
	}
}

void Entity::DrawSprite()
{
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Sprite);
	}
}

