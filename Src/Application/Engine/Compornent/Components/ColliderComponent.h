#pragma once
#include "../Component.h"
class ColliderComponent : public Component
{
public:
	ColliderComponent() = default;
	virtual ~ColliderComponent() = default;

	void Init()override;
	void Update()override;

	// 当たり判定形状を追加
	void AddSphereShape(const std::string & name, const Math::Vector3 & localPos, float radius, UINT type)
	{
		m_collider.RegisterCollisionShape(name, localPos, radius, type);
	}

	void AddBoxShape(const std::string & name, const Math::Matrix & transform, const Math::Vector3 & offset, const Math::Vector3 & size, UINT type, bool isOriented)
	{
		KdCollider::BoxInfo boxInfo(type, transform, offset, size, isOriented);
		if (!isOriented)
			m_collider.RegisterCollisionShape(name, boxInfo.m_Abox, type);
		else
			m_collider.RegisterCollisionShape(name, boxInfo.m_Obox, type);
	}

	void AddModelShape(const std::string & name, const std::shared_ptr<KdModelData>&model, UINT type)
	{
		m_collider.RegisterCollisionShape(name, model, type);
	}

	void AddPolygonShape(const std::string & name, const std::shared_ptr<KdPolygon>&polygon, UINT type)
	{
		m_collider.RegisterCollisionShape(name, polygon, type);
	}

	// 判定実行
	bool Intersects(const KdCollider::SphereInfo & target, const Math::Matrix & world, std::list<KdCollider::CollisionResult>*pRes = nullptr) const
	{
		return m_collider.Intersects(target, world, pRes);
	}

	bool Intersects(const KdCollider::BoxInfo & target, const Math::Matrix & world, std::list<KdCollider::CollisionResult>*pRes = nullptr) const
	{
		return m_collider.Intersects(target, world, pRes);
	}

	bool Intersects(const KdCollider::RayInfo & target, const Math::Matrix & world, std::list<KdCollider::CollisionResult>*pRes = nullptr) const
	{
		return m_collider.Intersects(target, world, pRes);
	}

	void SetEnable(const std::string & name, bool flag) { m_collider.SetEnable(name, flag); }
	void SetEnable(UINT type, bool flag) { m_collider.SetEnable(type, flag); }
	void SetEnableAll(bool flag) { m_collider.SetEnableAll(flag); }
private:
	KdCollider m_collider;
};

