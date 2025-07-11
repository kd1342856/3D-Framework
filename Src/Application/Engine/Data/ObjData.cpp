#include "ObjData.h"
#include "../Entity/Entity/Entity.h"
#include "../Entity/Component/Trans/TransformComponent.h"
#include "../Entity/Component/Render/RenderComponent.h"
std::vector<ObjData> ObjectData::ConvertToDataList(const std::vector<std::shared_ptr<Entity>>& entityList)
{
	std::vector<ObjData> result;
	for (const auto& ent : entityList)
	{
		if (!ent)continue;

		if (!ent || !ent->HasComponent<TransformComponent>())continue;

		const auto& tf = ent->GetComponent<TransformComponent>();

		ObjData data;
		data.pos = tf.GetPos();
		data.rot = tf.GetRotation();
		data.scale = tf.GetScale();

		result.push_back(data);
	}
	return result;
}

void ObjectData::SaveObj(const std::vector<ObjData>& objects, const std::string& filePath)
{
	json j;
	for (const auto& obj : objects)
	{
		j.push_back(obj.ToJson());
	}
	std::ofstream ofs(filePath);
	if (ofs)
	{
		ofs << j.dump(4);
	}
}

std::vector<ObjData> ObjectData::LoadJson(const std::string& filePath)
{
	std::vector<ObjData> result;
	std::ifstream ifs(filePath);

	if (!ifs)return result;

	json j;
	ifs >> j;

	for (auto& elem : j)
	{
		result.push_back(ObjData::FromJson(elem));
	}
	return result;
}

std::vector<std::shared_ptr<Entity>> ObjectData::LoadEntityList(const std::string& filePath)
{
	std::vector<std::shared_ptr<Entity>> entities;
	std::ifstream ifs(filePath);
	if (!ifs)return entities;

	json j;
	ifs >> j;

	for (auto& elem : j)
	{
		ObjData data = ObjData::FromJson(elem);
		auto ent = std::make_shared<Entity>();

		auto transform = std::make_shared<TransformComponent>();
		transform->SetPos(data.pos);
		transform->SetRotation(data.rot);
		transform->SetScale(data.scale);
		ent->AddComponent<TransformComponent>(transform);

		auto render = std::make_shared<RenderComponent>();
		ent->AddComponent<RenderComponent>(render);

		entities.push_back(ent);
	}
	return entities;
}

