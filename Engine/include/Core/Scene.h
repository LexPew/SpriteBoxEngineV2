#pragma once
#include <vector>
#include <memory>
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"

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

    const std::vector<std::shared_ptr<Entity>>& GetEntities() const
    {
        return m_entities;
    }

    void AddEntity(std::shared_ptr<Entity> p_entity)
    {
        m_entities.push_back(p_entity);
    }
	void Start()
	{
		for (auto& entity : m_entities)
		{
			entity->Start();
		}
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
	template<class Archive>
	void save(Archive& archive) const
	{
		archive(m_entities);
	}
	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_entities);
	}

};

