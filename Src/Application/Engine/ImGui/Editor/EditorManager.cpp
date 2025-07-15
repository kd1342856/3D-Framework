#include "EditorManager.h"
#include "EditorScene/EditorScene.h"
#include "EditorUI/EditorUI.h"
#include "EditorCamera/EditorCamera.h"

void EditorManager::Init()
{
	m_scene = std::make_shared<EditorScene>();
	m_ui = std::make_shared<EditorUI>();
	m_camera = std::make_shared<EditorCamera>();
	m_camera->Init();
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
	auto camera = m_camera->GetCamera();
	if (camera)
	{
		camera->SetToShader();
	}
	m_scene->Draw();
	m_ui->DrawEditorUI();
	m_ui->DrawEntityInspector();
}
