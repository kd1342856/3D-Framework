#include "EditorManager.h"
#include "EditorScene/EditorScene.h"
#include "EditorUI/EditorUI.h"
#include "../../../Scene/SceneManager.h"
#include "EditorCamera/EditorCamera.h"

void EditorManager::Init()
{
	m_scene = std::make_shared<EditorScene>();
	m_ui = std::make_shared<EditorUI>();
	m_camera = std::make_shared<EditorCamera>();
	m_camera->Init();
	SceneManager::Instance().AddObject(m_camera);
}

void EditorManager::Update()
{
	m_scene->Update();
}

void EditorManager::PostUpdate()
{
	m_camera->PostUpdate();
}

void EditorManager::Draw()
{
	if (!m_scene || !m_camera)return;
	auto camera = m_camera->GetCamera();
	if (camera)
	{
		camera->SetToShader();
	}
	m_scene->Draw();
	if (m_ui)
	{
		m_ui->Update(*this);
	}
}


EditorMode EditorManager::GetMode() const
{
	return m_scene->GetMode();
}

void EditorManager::SetMode(EditorMode mode)
{
	m_scene->SetMode(mode);
}

std::vector<std::shared_ptr<Entity>>& EditorManager::GetEntityList()
{
	return m_scene->GetEntityList();
}

void EditorManager::SetEntityList(const std::vector<std::shared_ptr<Entity>>& list)
{
	m_scene->GetEntityList() = list;
}

Math::Matrix EditorManager::GetCameraMatrix() const
{
	return m_camera ? m_camera->GetCamera()->GetCameraViewMatrix() :
		Math::Matrix::Identity;
}

bool EditorManager::IsEditorMode() const
{
	return m_scene && m_scene->IsEditorMode();
}
