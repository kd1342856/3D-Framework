#include "RenderComponent.h"
#include "../Entity.h"
#include "TransformComponent.h"
void RenderComponent::Draw(DrawPass pass)
{
	auto owner = m_owner.lock();
	if (!owner)return;

	if (!owner->HasComponent<TransformComponent>())return;
	const auto& transform = owner->GetComponent<TransformComponent>();
	const Math::Matrix& world = transform.GetMatrix();

	// ModelWork（動的モデル）がある場合
	if (m_modelWork && m_modelWork->IsEnable())
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, world, m_colorRate, m_emissive);
		return;
	}

	// ModelData（静的モデル）のみある場合（例：地形など）
	if (m_modelData)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelData, world, m_colorRate, m_emissive);
	}

	switch (pass) {
	case DrawPass::Lit:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, world, m_colorRate, m_emissive);
		break;
	case DrawPass::UnLit:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, world);
		break;
	case DrawPass::Bright:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, world);
		break;
	case DrawPass::Shadow:
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_modelWork, world);
		break;
	}
}
void RenderComponent::SetModel(const std::shared_ptr<KdModelData>& modelData)
{
	m_modelData = modelData;
	if (!m_modelWork) m_modelWork = std::make_shared<KdModelWork>();
	m_modelWork->SetModelData(m_modelData);
}
void RenderComponent::SetModel(const std::shared_ptr<KdModelWork>& modelWork)
{
	m_modelWork = modelWork;
}
