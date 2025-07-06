#include "Entity.h"
#include "Component/Component.h"

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
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Lit);
	}
}

void Entity::DrawUnLit()
{
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::UnLit);
	}
}

void Entity::DrawEffect()
{
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Effect);
	}
}

void Entity::DrawBright()
{
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Bright);
	}
}

void Entity::GenerateDepthMapFromLight()
{
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Shadow);
	}
}

void Entity::DrawSprite()
{
	if (!IsVisible())return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Sprite);
	}
}

