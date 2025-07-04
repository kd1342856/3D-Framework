#include "TransformComponent.h"

void TransformComponent::Update()
{
}

const Math::Matrix& TransformComponent::GetMatrix() const
{
	if (m_dirty)
	{
		using namespace DirectX;
		auto scale = Math::Matrix::CreateScale(m_scale);
		auto rotY = Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_rotation.x),
			DirectX::XMConvertToRadians(m_rotation.y),
			DirectX::XMConvertToRadians(m_rotation.z));
		auto trans = Math::Matrix::CreateTranslation(m_pos);
		m_matrix = scale * rotY * trans;
		m_dirty = false;
	}
	return m_matrix;
}
