#pragma once
#include <typeindex>

class Component;
class Entity : public KdGameObject
{
public:
	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawUnLit()override;
	void DrawEffect()override;
	void DrawBright()override;
	void GenerateDepthMapFromLight()override;
	void DrawSprite()override;
	bool IsVisible()const override{ return m_visible; }
	void SetVisible(bool visible) { m_visible = visible; }

	template<typename T>
	void AddComponent(std::shared_ptr<Component> comp);

	template<typename T>
	bool HasComponent() const;

	template<typename T>
		T& GetComponent();

private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	bool m_visible = true;
};
#include "Entity.inl"
