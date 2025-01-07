#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Component.h"
#include "TransformComponent.h"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/polymorphic.hpp"
#include "cereal/types/unordered_map.hpp"
#include "Debug/DebugMacros.h"


class Renderer;

class Entity
{
protected:
    std::string name{ "Entity" };
    bool active{ true };
    std::unordered_map<std::string, std::shared_ptr<Component>> m_components;
public:
    Entity()
    {
        AddTransform(Vector2::Zero(), Vector2::Zero());
    }
    Entity(const std::string& p_name) : name(p_name)
    {
        AddTransform(Vector2::Zero(), Vector2::Zero());
    }

    Entity(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale) : name(p_name)
    {
        AddTransform(p_position, p_scale);
    }

    virtual ~Entity()
    {
        for (auto m : m_components)
        {
            m.second.reset();
        }
    }

    std::string GetName() const { return name; }
	void SetName(const std::string& p_name) { name = p_name; }
    void AddTransform(const Vector2& p_position, const Vector2& p_scale);
    /**
     * Adds a component to this entity if we don't have one already
     */
    template<typename T>
    bool AddComponent(std::shared_ptr<T> p_component);

	template <typename T>
	bool RemoveComponent(T p_component)
	{
		std::string typeName = typeid(T).name();
		auto it = m_components.find(typeName);
		if (it != m_components.end())
		{
			m_components.erase(it);
			return true;
		}
		return false;
	}
    /**
     * Gets a component of the specified type if it exists
     */
    template<typename T>
    std::shared_ptr<T> GetComponent();
    template <class T>
    std::shared_ptr<T> GetComponentByType();

    /**
	 * Called when the entity is created, used to set up initial state
     */
    virtual void Awake();
    /**
     * Call start on all components attached to this entity
     */
    virtual void Start();
    /**
     * Updates all components attached to this entity
     */
    virtual void Update(float p_deltaTime);

    /**
     * Renders all components attached to this entity
     */
    virtual void Render(Renderer& p_renderer);

    /**
     * Returns the transform component of this entity
     */
    std::shared_ptr<TransformComponent> GetTransform() { return GetComponent<TransformComponent>(); }


    template <class Archive>
    void save(Archive& ar) const
    {

        ar(name, active, m_components);
		DEBUG_LOG("Entity saved");
    }

    template <class Archive>
    void load(Archive& ar)
    {
		ar(name, active, m_components);
   
		for (auto& pair : m_components)
		{
			pair.second->owner = this;
		}
		DEBUG_LOG("Entity loaded");
    }

};

template <typename T>
bool Entity::AddComponent(std::shared_ptr<T> p_component)
{
    std::string typeName = typeid(T).name();
    if (m_components.find(typeName) == m_components.end())
    {
        m_components[typeName] = p_component;
        p_component->owner = this;
        return true;
    }
    return false;
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent()
{
    std::string typeName = typeid(T).name();
    auto it = m_components.find(typeName);
    if (it != m_components.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}

template<typename T>
std::shared_ptr<T> Entity::GetComponentByType()
{
	for (auto& pair : m_components)
	{
		if (auto component = std::dynamic_pointer_cast<T>(pair.second))
		{
			return component;
		}
	}
	return nullptr;
}
CEREAL_REGISTER_TYPE(Entity)

