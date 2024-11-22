#pragma once
#include <vector>
#include <memory>
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"

class Scene
{
private:
    std::vector<std::shared_ptr<Entity>> m_entities;

public:
	std::shared_ptr<Entity> FindEntityByName(const std::string& p_name)
	{
		for (auto& entity : m_entities)
		{
			if (entity->GetName() == p_name)
			{
				return entity;
			}
		}
		return nullptr;
	}
    void AddEntity(std::shared_ptr<Entity> p_entity)
    {
        m_entities.push_back(p_entity);
    }

    void Update(float p_deltaTime)
    {
        for (auto& entity : m_entities)
        {
            entity->Update(p_deltaTime);
        }
    }

    void Render(Renderer& p_renderer)
    {
        for (auto& entity : m_entities)
        {
            entity->Render(p_renderer);
        }
    }

    void Serialize(nlohmann::json& p_json)
    {
		p_json["entities"] = nlohmann::json::array();
		for (auto& entity : m_entities)
		{
			nlohmann::json entityJson;
            entity->Serialize(entityJson);
            p_json["entities"].push_back(entityJson);
		}
    }

    void Deserialize(const nlohmann::json& p_json)
    {
		for (const auto& entity_json : p_json.at("entities"))
		{
			auto entity = std::make_shared<Entity>();
			entity->Deserialize(entity_json);
            AddEntity(entity);
		}
    }

};
