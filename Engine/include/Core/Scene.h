#pragma once
#include <vector>
#include <memory>
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"
#include "ECS/Actor.h"
#include "ECS/Solid.h"

class Scene
{
private:
    std::vector<std::shared_ptr<Entity>> m_entities;

	//Derived from m_entities
	std::vector<std::shared_ptr<Actor>> m_actors;
	std::vector<std::shared_ptr<Solid>> m_solids;

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
	const std::vector<std::shared_ptr<Actor>>& GetActors() const
	{
		return m_actors;
	}
	const std::vector<std::shared_ptr<Solid>>& GetSolids() const
	{
		return m_solids;
	}
	void AddEntity(std::shared_ptr<Entity> p_entity)
	{
		if (!p_entity) {
			// Handle the error, log it, or return early
			return;
		}

		m_entities.push_back(p_entity);

		// Check if the entity is an actor or solid
		if (auto actor = std::dynamic_pointer_cast<Actor>(p_entity))
		{
			m_actors.push_back(actor);
		}
		else if (auto solid = std::dynamic_pointer_cast<Solid>(p_entity))
		{
			m_solids.push_back(solid);
		}
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
		archive(m_entities, m_actors, m_solids);
	}
	template<class Archive>
	void load(Archive& archive)
	{
		archive(m_entities, m_actors, m_solids);
	}
};

