#pragma once
using json = nlohmann::json;
class Entity;
struct ObjData
{
	std::string name;
	Math::Vector3 pos;
	Math::Vector3 rot;
	Math::Vector3 scale;

	json ToJson()const
	{
		return
		{
			{"name", name},
			{"pos", { pos.x, pos.y, pos.z }},
			{"rot", { rot.x, rot.y, rot.z }},
			{"scale", { scale.x, scale.y, scale.z }}
		};
	}

	static ObjData FromJson(const json& j)
	{
		ObjData obj;
		obj.name = j.at("name");
		auto pos = j.at("pos");
		auto rot = j.at("rot");
		auto scale = j.at("scale");
		obj.pos = { pos[0], pos[1], pos[2] };
		obj.rot = { rot[0], rot[1], rot[2] };
		obj.scale = { scale[0], scale[1], scale[2] };
		return obj;
	}
};
class ObjectData
{
public:
	ObjectData(){}
	~ObjectData(){}
	std::vector<ObjData> ConvertToDataList(const std::vector<std::shared_ptr<Entity>>& entityList);

	void SaveObj(const std::vector<ObjData>& objects, const std::string& filePath);
	std::vector<ObjData> LoadJson(const std::string& filePath);
	std::vector<std::shared_ptr<Entity>> LoadEntityList(const std::string& filePath);
	
private:


};
