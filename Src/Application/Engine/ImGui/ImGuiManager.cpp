#include "ImGuiManager.h"
#include "../../main.h"
#include "../Entity/Entity.h"
#include "../Entity/Component/Trans/TransformComponent.h"
#include "../Entity/Component/Render/RenderComponent.h"
#include "../Engine.h"
void ImGuiManager::GuiInit()
{

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
	io.ConfigFlags | !ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontDefault();
	// 日本語対応
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\msgothic.ttc", 13.0f, &config, glyphRangesJapanese);

}

void ImGuiManager::GuiProcess()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	//===========================================================
	// 以下にImGui描画処理を記述
	//==========================================================
	
	DrawEntityInspector();
	DrawEditorUI();
	GameScreen();
	EngineCore::Logger::DrawImGui();
	//===========================================================
	// ここより上にImGuiの描画はする事
	//===========================================================
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

void ImGuiManager::DrawEditorUI()
{
	//	Entity List
	ImGui::Begin("Hierarchy");
	if (ImGui::Button("Add Object"))
	{
		auto newEnt = std::make_shared<Entity>();
		// 必要なコンポーネント追加
		auto transform = std::make_shared<TransformComponent>();
		newEnt->AddComponent<TransformComponent>(transform);

		auto render = std::make_shared<RenderComponent>();
		newEnt->AddComponent<RenderComponent>(render);

		m_entityList->push_back(newEnt);
		EngineCore::Logger::Add("New Entity Created\n");
	}
	for (size_t i = 0; i < m_entityList->size(); ++i)
	{
		std::string label = "Entity " + std::to_string(i);
		if (ImGui::Selectable(label.c_str(), m_selectedEntityIndex == static_cast<int>(i)))
		{
			m_selectedEntityIndex = static_cast<int>(i);

		}
	}
	ImGui::End();
}

void ImGuiManager::DrawEntityInspector()
{
	//	Entity Inspector
	if (m_selectedEntityIndex >= 0 && m_selectedEntityIndex < static_cast<int>(m_entityList->size()))
	{
		auto& ent = (*m_entityList)[m_selectedEntityIndex];
		ImGui::Begin("Inspector");

		//	Transform編集
		if (ent->HasComponent<TransformComponent>())
		{
			auto& tf = ent->GetComponent<TransformComponent>();
			Math::Vector3 pos = tf.GetPos();
			Math::Vector3 rot = tf.GetRotation();

			if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) tf.SetPos(pos);
			if (ImGui::DragFloat3("Rotation", &rot.x, 1.0f)) tf.SetRotation(rot);
		}

		// 表示切り替え
		if (ent->HasComponent<RenderComponent>())
		{
			static bool visible = true; // 仮にEntityにm_visibleがないならここを状態保存
			if (ImGui::Checkbox("Visible", &visible))
			{
				ent->SetVisible(visible);
			}
		}

		ImGui::End();
	}
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
