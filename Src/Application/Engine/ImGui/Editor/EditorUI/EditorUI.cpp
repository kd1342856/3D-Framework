#include "EditorUI.h"
#include "../../../Entity/Component/Trans/TransformComponent.h"
#include "../../../Entity/Component/Render/RenderComponent.h"
#include "../../../Entity/Entity/Entity.h"
void EditorUI::DrawEditorUI()
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

		m_entityList.push_back(newEnt);
		EngineCore::Logger::Add("New Entity Created\n");
	}
	for (size_t i = 0; i < m_entityList.size(); ++i)
	{
		std::string label = "Entity " + std::to_string(i);
		if (ImGui::Selectable(label.c_str(), m_selectedEntityIndex == static_cast<int>(i)))
		{
			m_selectedEntityIndex = static_cast<int>(i);
		}
	}
	ImGui::End();
}

void EditorUI::DrawEntityInspector()
{
	if (m_selectedEntityIndex >= 0 && m_selectedEntityIndex < static_cast<int>(m_entityList.size()))
	{
		auto ent = (m_entityList)[m_selectedEntityIndex];
		ImGui::Begin("Inspector");
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{//	Transform編集
			if (ent->HasComponent<TransformComponent>())
			{
				auto& tf = ent->GetComponent<TransformComponent>();
				Math::Vector3 pos = tf.GetPos();
				Math::Vector3 rot = tf.GetRotation();
				Math::Vector3 scale = tf.GetScale();

				if (ImGui::DragFloat3("Position", &pos.x, 0.1f)) tf.SetPos(pos);
				if (ImGui::DragFloat3("Rotation", &rot.x, 1.0f)) tf.SetRotation(rot);
				if (ImGui::DragFloat3("Scale", &scale.x, 1.0f)) tf.SetScale(scale);
			}
		}

		// 表示切り替え
		if (ent->HasComponent<RenderComponent>())
		{
			if (ImGui::CollapsingHeader("Render Setting", ImGuiTreeNodeFlags_DefaultOpen))
			{
				using VF = Entity::VisibilityFlags;

				bool lit	= ent->IsVisible(VF::Lit);
				bool unlit	= ent->IsVisible(VF::UnLit);
				bool bright = ent->IsVisible(VF::Bright);
				bool shadow = ent->IsVisible(VF::Shadow);

				if (ImGui::Checkbox("DrawLit", &lit))							ent->SetVisibility(VF::Lit, lit);
				if (ImGui::Checkbox("DrawUnLit", &unlit))						ent->SetVisibility(VF::UnLit, unlit);
				if (ImGui::Checkbox("DrawBright", &bright))						ent->SetVisibility(VF::Bright, bright);
				if (ImGui::Checkbox("GenerateDepthMapFromLight", &shadow))		ent->SetVisibility(VF::Shadow, shadow);
			}
		}
		ImGui::End();
	}
}
