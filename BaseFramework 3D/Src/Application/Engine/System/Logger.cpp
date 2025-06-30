#include "Logger.h"

void EngineCore::Logger::Log(const std::string& category, const std::string& msg)
{
	std::lock_guard<std::mutex> lock(s_mutex);
	std::cout << "[" << category << "]" << msg << std::endl;
	s_logs.push_back({ category, GetTimestamp() + " " + msg });
}

void EngineCore::Logger::Error(const std::string& msg)
{
	Log("Error", msg);
}

void EngineCore::Logger::DrawImGui()
{
	std::lock_guard<std::mutex> lock(s_mutex);
	if (ImGui::BeginChild("Log Window"))
	{
		if (ImGui::BeginTabBar("LogTabs"))
		{
			std::set<std::string> categories;
			for (const auto& log : s_logs)
			{
				categories.insert(log.category);
			}
			//	表示を許可するカテゴリ
			static std::set<std::string> enabledCategories = { "Error", "System", "Task" };
			
			for (const auto& cat : categories)
			{
				if (enabledCategories.count(cat) == 0) continue; // フィルタに引っかかったらスキップ

				if (ImGui::BeginTabItem(cat.c_str()))
				{
					if (ImGui::BeginChild((cat + "_scroll").c_str(), ImVec2(0, 0), true))
					{
						for (const auto& log : s_logs)
						{
							if (log.category == cat)
							{
								ImGui::TextWrapped("%s", log.message.c_str());
							}
						}
						ImGui::EndTabItem();
					}
					ImGui::EndChild();
				}
			}
			ImGui::EndTabBar();
		}
		if (ImGui::Button("Clear"))
		{
			s_logs.clear();
		}
	}
	ImGui::End();
}
