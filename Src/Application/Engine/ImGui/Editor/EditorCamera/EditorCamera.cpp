#include "EditorCamera.h"

void EditorCamera::Init()
{
	CameraBase::Init();
	m_mLocalPos = Math::Matrix::Identity;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void EditorCamera::PostUpdate()
{
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

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		UpdateRotateByMouse();
	}
	move *= speed;

	Math::Matrix rotY = GetRotationMatrix();
	Math::Vector3 forward = move;
	forward = DirectX::XMVector3TransformCoord(forward, rotY);

	m_mLocalPos *= Math::Matrix::CreateTranslation(forward);

	m_mWorld = m_mRotation * m_mLocalPos;
}
