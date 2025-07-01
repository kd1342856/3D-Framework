#pragma once
class Entity;
class Component
{
public:
	virtual ~Component(){}
	virtual void Update(){}
	virtual void Draw(){}

	void SetOwner(std::shared_ptr<Entity>owner) { m_owner = owner; }

private:
	std::weak_ptr<Entity> m_owner;
};
