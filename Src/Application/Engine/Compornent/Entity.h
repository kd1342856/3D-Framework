#pragma once
#include <typeindex>

class Component;
class Entity :public std::enable_shared_from_this<Entity>
{
public:
	void Update();
	void Draw();
	void AddComponent(std::shared_ptr<Component> comp);

	template<typename T>
	bool HasComponent() const;

	template<typename T>
		T& GetComponent();

private:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
};

template<typename T>
inline bool Entity::HasComponent() const
{
	return m_components.find(typeid(T)) != m_components.end();
}

template<typename T>
inline T& Entity::GetComponent()
{
	auto it = m_components.find(typeid(T));
	if (it == m_components.end()) {
		throw std::runtime_error("Component not found");
	}
	auto compPtr = std::dynamic_pointer_cast<T>(it->second);
	if (!compPtr) {
		throw std::runtime_error("Component type mismatch");
	}
	return *compPtr;
}
