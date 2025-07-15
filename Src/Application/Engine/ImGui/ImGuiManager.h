#pragma once
#include "Editor/EditorScene/EditorScene.h"
class EditorCamera;
class Entity;
class EditorUI;
class ImGuiManager
{
public:
	void GuiInit();
	void GuiProcess();
	std::shared_ptr<EditorUI> m_editorUI;
	EditorScene* GetEditorScene() { return m_editorScene.get(); }

private:
	void GuiRelease();

	void GameScreen();
	void DrawMainMenu();
	void DrawGame();
	std::unique_ptr<EditorScene> m_editorScene;
	std::shared_ptr<EditorCamera> m_editorCamera;
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
