#include "ImGuiManager.h"
#include "../../main.h"
#include "../Entity/Entity/Entity.h"
#include "../Entity/Component/Trans/TransformComponent.h"
#include "../Entity/Component/Render/RenderComponent.h"
#include "../Engine.h"
#include "../../Scene/SceneManager.h"
#include "../Data/ObjData.h"
#include "Editor/EditorUI/EditorUI.h"
#include "Editor/EditorScene/EditorScene.h"
#include "Editor/EditorCamera/EditorCamera.h"

void ImGuiManager::GuiInit()
{
	m_editorCamera = std::make_shared<EditorCamera>();
	m_editorUI = std::make_shared<EditorUI>();
	m_editorScene = std::make_unique<EditorScene>();
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();
	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(Application::Instance().GetWindowHandle());
	ImGui_ImplDX11_Init(
		KdDirect3D::Instance().WorkDev(), KdDirect3D::Instance().WorkDevContext());

#include "imgui/ja_glyph_ranges.h"
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.MergeMode = true;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	io.Fonts->AddFontDefault();
	// 日本語対応
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);
}

void ImGuiManager::GuiProcess()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (m_editorScene->GetMode() == EditorMode::Editor)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		
		//===========================================================
		// 以下にImGui描画処理を記述
		//==========================================================

		DrawMainMenu();
		m_editorScene->Draw();
		if (m_editorScene->IsEditorMode())
		{
			GameScreen();
			m_editorUI->DrawEditorUI();
			m_editorUI->DrawEntityInspector();
		}
		//===========================================================
		// ここより上にImGuiの描画はする事
		//===========================================================
	}
	else if (m_editorScene->GetMode() == EditorMode::Game)
	{
		DrawGame();
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
}

void ImGuiManager::GuiRelease()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::GameScreen()
{
	ImGui::Begin("GameScreen");
	if (EngineCore::Engine::Instance().m_gameViewRT)
	{
		ID3D11ShaderResourceView* srv = EngineCore::Engine::Instance().m_gameViewRT->GetSRView();
		if (srv)
		{
			ImVec2 size = ImGui::GetContentRegionAvail();
			ImGui::Image((ImTextureID)srv, size);
		}
	}
	ImGui::End();
}

void ImGuiManager::DrawMainMenu()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			auto objData = std::make_shared<ObjectData>();
			if (ImGui::MenuItem("Save"))
			{
				auto entityList = m_editorUI->GetEntityList();
				auto objList = objData->ConvertToDataList(entityList);
				objData->SaveObj(objList, "Asset/Data/ObjData/ObjData/ObjData.json");
			}
			if (ImGui::MenuItem("Load"))
			{
				auto newEntities = objData->LoadEntityList("Asset/Data/ObjData/ObjData/ObjData.json");
				m_editorUI->SetEntityList(newEntities);
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Mode"))
		{
			if (ImGui::MenuItem("Editor Mode"))
			{
				m_editorScene->SetMode(EditorMode::Editor);
			}
			if (ImGui::MenuItem("Game Mode"))
			{
				m_editorScene->SetMode(EditorMode::Game);
			}
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();
}

void ImGuiManager::DrawGame()
{
	if (!EngineCore::Engine::Instance().m_gameViewRT) return;

	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground;

	ImVec2 vpSize = ImGui::GetMainViewport()->Size;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(vpSize);

	ImGui::Begin("##GameFullscreen", nullptr, flags);

	ID3D11ShaderResourceView* srv = EngineCore::Engine::Instance().m_gameViewRT->GetSRView();
	if (srv)
	{
		ImGui::Image((ImTextureID)srv, vpSize);
	}

	ImGui::End();
}
