#pragma once
class Entity;
class ImGuiManager
{
public:
	void GuiInit();
	void GuiProcess();
	void GameScreen();


	void SetEntityList(std::vector<std::shared_ptr<Entity>>* list) { m_entityList = list; }

private:
	void GuiRelease();
	void DrawEditorUI();
	void DrawEntityInspector();

	std::vector<std::shared_ptr<Entity>>* m_entityList = nullptr;
	int m_selectedEntityIndex = -1;
private:
	ImGuiManager() {}
	~ImGuiManager() { GuiRelease(); }
public:
	static ImGuiManager& Instance() 
	{
		static ImGuiManager Instance;
		return Instance;
	}
};
