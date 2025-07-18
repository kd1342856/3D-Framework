#include "RenderComponent.h"
#include "../../Entity/Entity.h"
#include "../Trans/TransformComponent.h"
void RenderComponent::Draw()
{
	auto owner = m_owner.lock();
	if (!owner)return;

	if (!owner->HasComponent<TransformComponent>())return;
	const auto& transform = owner->GetComponent<TransformComponent>();
	const Math::Matrix& world = transform.GetMatrix();
	
	auto& shader = KdShaderManager::Instance().m_StandardShader;

	if (m_modelWork && m_modelWork->IsEnable())
	{
		if (owner->IsVisible(Entity::VisibilityFlags::Lit))
		{
			shader.DrawModel(*m_modelWork, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::UnLit))
		{
			shader.DrawModel(*m_modelWork, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::Bright))
		{
			shader.DrawModel(*m_modelWork, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::Shadow))
		{
			shader.DrawModel(*m_modelWork, world);
		}
	}
	else if (m_modelData)
	{
		if (owner->IsVisible(Entity::VisibilityFlags::Lit))
		{
			shader.DrawModel(*m_modelData, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::UnLit))
		{
			shader.DrawModel(*m_modelData, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::Bright))
		{
			shader.DrawModel(*m_modelData, world);
		}
		if (owner->IsVisible(Entity::VisibilityFlags::Shadow))
		{
			shader.DrawModel(*m_modelData, world);
		}
	}
}

void RenderComponent::SetModelData(const std::string& filePath)
{
	m_modelData->Load(filePath);
	m_modelType = ModelType::Static;
}

void RenderComponent::SetModelWork(const std::string& filePath)
{
	m_modelWork->SetModelData(filePath);
	m_modelType = ModelType::Dynamic;
}
