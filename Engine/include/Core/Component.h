#pragma once
#include <Utils/json.hpp>
class Entity;
class Renderer;

class Component
{
public:
	Entity* owner{ nullptr };
	virtual ~Component() = default;
	virtual void Start() = 0;
	virtual void Update(float p_deltaTime) = 0;
	virtual void Render(Renderer& p_renderer) = 0;

	//Serialization
	virtual void Serialize(nlohmann::json& p_json) = 0;
	virtual void Deserialize(const nlohmann::json& p_json) = 0;
};

