#pragma once
class Entity;
class EditorManager;
class ImGuiManager
{
public:
	void GuiInit();
	void GuiProcess();

private:
	void GuiRelease();
	std::shared_ptr<EditorManager> m_editor;

	void GameScreen();
	void DrawMainMenu();
	void DrawGame();

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
