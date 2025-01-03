#pragma once
#include <vector>
#include <memory>
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"
#include "Debug/DebugMacros.h"
#include "ECS/Actor.h"
#include "ECS/Solid.h"
#include "ECS/UI/UIButton.h"
#include "ECS/UI/UIComponent.h"
#include "Core/AssetManager.h"
class Scene
{
private:
    std::vector<std::shared_ptr<Entity>> m_entities;

	//Derived from m_entities
	std::vector<std::shared_ptr<Actor>> m_actors;
	std::vector<std::shared_ptr<Solid>> m_solids;

public:
	Scene() = default;
	~Scene()
	{
		m_entities.clear();
		m_actors.clear();
		m_solids.clear();
	}
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
	std::vector<std::shared_ptr<Solid>>& GetSolids()
	{
		return m_solids;
	}
	void AddEntity(const std::shared_ptr<Entity>& p_entity)
	{
		if (!p_entity) {
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
	virtual void Start() 
	{
		for (auto& entity : m_entities)
		{
			entity->Start();
		}
	}
    virtual void Update(float p_deltaTime)
    {
        for (auto& entity : m_entities)
        {
            entity->Update(p_deltaTime);
        }
    }

    virtual void Render(Renderer& p_renderer)
    {
		Renderer::GetInstance().DrawBackground();
        for (auto& entity : m_entities)
        {
            entity->Render(p_renderer);

        }
    }

	virtual void HandleInput(const Vector2& p_mousePosition, const bool p_click)
	{
		for (auto& entity : m_entities)
		{
			auto uiComponent = entity->GetComponentByType<UIComponent>();
			if(uiComponent != nullptr)
			{
				uiComponent->HandleInput(p_mousePosition, p_click);
			}

		}
	}
	template<class Archive>
	void save(Archive& archive) const
	{
		// Save the assets used in this scene
		AssetManager::GetInstance().save(archive);

		archive(m_entities, m_actors, m_solids);
	}

	template<class Archive>
	void load(Archive& archive)
	{
		// Load the assets used in this scene
		AssetManager::GetInstance().load(archive);

		archive(m_entities, m_actors, m_solids);
	}
};

