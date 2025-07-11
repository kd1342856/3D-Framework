#include "Entity.h"
#include "../Component/Component.h"

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
	if (!IsVisible(VisibilityFlags::Lit))return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Lit);
	}
}

void Entity::DrawUnLit()
{
	if (!IsVisible(VisibilityFlags::UnLit))return;
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
	if (!IsVisible(VisibilityFlags::Bright))return;
	for (auto& [type, comp] : m_components)
	{
		comp->Draw(Component::DrawPass::Bright);
	}
}

void Entity::GenerateDepthMapFromLight()
{
	if (!IsVisible(VisibilityFlags::Shadow))return;
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

void Entity::SetVisibility(VisibilityFlags flag, bool enabled)
{
	if (enabled)
	{
		m_visibility |= static_cast<uint8_t>(flag);
	}
	else
	{
		m_visibility &= ~static_cast<uint8_t>(flag);
	}
}
