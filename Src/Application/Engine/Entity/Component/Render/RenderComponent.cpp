#include "RenderComponent.h"
#include "../../Entity/Entity.h"
#include "../Trans/TransformComponent.h"
void RenderComponent::Draw(DrawPass pass)
{
	auto owner = m_owner.lock();
	if (!owner)return;

	if (!owner->HasComponent<TransformComponent>())return;
	const auto& transform = owner->GetComponent<TransformComponent>();
	const Math::Matrix& world = transform.GetMatrix();
	
	auto& shader = KdShaderManager::Instance().m_StandardShader;

	if (m_modelWork && m_modelWork->IsEnable())
	{
		switch (pass) 
		{
		case DrawPass::Lit:
			shader.DrawModel(*m_modelWork, world);
			break;
		case DrawPass::UnLit:
		case DrawPass::Bright:
		case DrawPass::Shadow:
			shader.DrawModel(*m_modelWork, world);
			break;
		}
	}

	if (m_modelData)
	{
		switch (pass)
		{
		case DrawPass::Lit:
			shader.DrawModel(*m_modelWork, world);
			break;
		case DrawPass::UnLit:
		case DrawPass::Bright:
		case DrawPass::Shadow:
			shader.DrawModel(*m_modelData, world);
			break;
		}
	}
}

void RenderComponent::SetModel(const std::shared_ptr<KdModelData>& modelData)
{
	m_modelData = modelData;
	m_modelType = ModelType::Static;

	if (!m_modelWork)
	{
		m_modelWork = std::make_shared<KdModelWork>();
		m_modelWork->SetModelData(m_modelData);
	}
}

void RenderComponent::SetModel(const std::shared_ptr<KdModelWork>& modelWork)
{
	m_modelWork = modelWork;
	m_modelType = ModelType::Dynamic;
}
