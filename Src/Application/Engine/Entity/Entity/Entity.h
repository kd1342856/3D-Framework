#pragma once
#include <typeindex>

class Component;
class Entity : public KdGameObject, public std::enable_shared_from_this<Entity>
{
public:
	enum class VisibilityFlags :uint8_t
	{
		None   = 0,
		Lit	   = 1 << 0,
		UnLit  = 1 << 1,
		Bright = 1 << 2,
		Shadow = 1 << 3,
	};

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawUnLit()override;
	void DrawEffect()override;
	void DrawBright()override;
	void GenerateDepthMapFromLight()override;
	void DrawSprite()override;


	void SetVisible(bool visible) { m_visible = visible; }

	void SetVisibility(VisibilityFlags flag, bool enabled);
	bool IsVisible(VisibilityFlags flag)const { return (m_visibility & static_cast<uint8_t>(flag)) != 0; }

	template<typename T>
	void AddComponent(std::shared_ptr<Component> comp);

	template<typename T>
	bool HasComponent() const;

	template<typename T>
		T& GetComponent();

private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
	bool m_visible = true;
	uint8_t m_visibility;
};
#include "Entity.inl"
