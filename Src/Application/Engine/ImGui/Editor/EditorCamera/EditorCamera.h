#pragma once
#include "../../../../GameObject/Camera/CameraBase.h"
class EditorCamera : public CameraBase
{
public:
	EditorCamera(){}
	~EditorCamera(){}

	void Init()override;
	void PostUpdate()override;

private:
	float m_moveSpeed = 0.3f;
};
