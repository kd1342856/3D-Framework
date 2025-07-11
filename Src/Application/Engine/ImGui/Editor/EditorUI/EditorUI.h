#pragma once
class Entity;
class EditorUI
{
public:
	EditorUI(){}
	~EditorUI(){}

	void DrawEditorUI();
	void DrawEntityInspector();

	void SetEntityList(const std::vector<std::shared_ptr<Entity>>& list) { m_entityList = list; }
	const std::vector<std::shared_ptr<Entity>>& GetEntityList() const { return m_entityList; }
	int GetSelectedIndex() { return m_selectedEntityIndex; }
private:
	std::vector<std::shared_ptr<Entity>> m_entityList;
	int m_selectedEntityIndex = -1;
};