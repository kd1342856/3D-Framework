#include "EditorCamera.h"
#include "../../../Engine.h"
void EditorCamera::Init()
{
	CameraBase::Init();
	m_mLocalPos = Math::Matrix::Identity;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void EditorCamera::PostUpdate()
{
	if (!EngineCore::Engine::Instance().m_isCameraControlActive)return;

	UpdateRotateByMouse();
	m_mRotation = GetRotationMatrix();

	Math::Vector3 move = Math::Vector3::Zero;

	if (GetAsyncKeyState('W') & 0x8000) move.z += 1.0f;
	if (GetAsyncKeyState('S') & 0x8000) move.z -= 1.0f;
	if (GetAsyncKeyState('A') & 0x8000) move.x -= 1.0f;
	if (GetAsyncKeyState('D') & 0x8000) move.x += 1.0f;
	if (GetAsyncKeyState('E') & 0x8000) move.y += 1.0f;
	if (GetAsyncKeyState('Q') & 0x8000) move.y -= 1.0f;

	float speed = m_moveSpeed;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		speed *= 3.0f;
	}
	move *= speed;

	Math::Matrix rot = GetRotationMatrix();
	Math::Vector3 forward = move;
	forward = DirectX::XMVector3TransformNormal(forward, rot);

	m_mLocalPos *= Math::Matrix::CreateTranslation(forward);

	m_mWorld = m_mRotation * m_mLocalPos;
}

Math::Matrix EditorCamera::GetCameraMatrix() const
{
	return m_mWorld.Invert();
}
