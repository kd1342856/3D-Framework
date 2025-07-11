#pragma once
enum class EditorMode
{
	Editor,
	Game
};
class EditorScene
{
public:
	EditorScene(){}
	~EditorScene(){}

	void Draw();
	void SetMode(EditorMode mode) { m_mode = mode; }
	EditorMode GetMode()const { return m_mode; }
	bool IsEditorMode()const { return m_mode == EditorMode::Editor; }
private:
	EditorMode m_mode = EditorMode::Editor;

};
