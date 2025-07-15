#pragma once
class EditorScene;
class EditorUI;
class EditorCamera;
class EditorManager
{
public:

	void Init();
	void Update();
	void PostUpdate();
	void Draw();

	Math::Matrix GetCameraMatrix()const
	{
		return m_camera ? 
			m_camera->GetCamera()->GetCameraViewMatrix() : 
			Math::Matrix::Identity;
	}

	std::shared_ptr<EditorCamera> GetCamera()const { return m_camera; }
	std::shared_ptr<EditorScene> GetScene()const { return m_scene; }

private:
	std::shared_ptr<EditorScene>	m_scene;
	std::shared_ptr<EditorUI>		m_ui;
	std::shared_ptr<EditorCamera>	m_camera;

};