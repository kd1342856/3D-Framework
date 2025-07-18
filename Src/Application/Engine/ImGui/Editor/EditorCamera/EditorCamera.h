#pragma once
#include "../../../../GameObject/Camera/CameraBase.h"
class EditorCamera : public CameraBase
{
public:
	EditorCamera(){}
	~EditorCamera(){}

	void Init()override;
	void PostUpdate()override;

	Math::Matrix GetCameraMatrix()const;


private:
	float m_moveSpeed = 0.3f;
	bool m_isControlling = false;
};
