#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>


#include "Component.h"
#include "TransformComponent.h"

class Renderer;

class Entity
{
private:
    std::string name{ "Entity" };
    bool active{ true };
    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_components;
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
        AddTransform(p_position,   p_scale);
    }

    ~Entity() = default;

	std::string GetName() const { return name; }
    void AddTransform(const Vector2& p_position, const Vector2& p_scale);
    /**
     * Adds a component to this entity if we don't have one already
     */
    template<typename T>
    bool AddComponent(std::shared_ptr<T> p_component);

    /**
     * Gets a component of the specified type if it exists
     */
    template<typename T>
    std::shared_ptr<T> GetComponent();

    /**
     * Call start on all components attached to this entity
     */
    void Start();
    /**
     * Updates all components attached to this entity
     */
    void Update(float p_deltaTime);

    /**
     * Renders all components attached to this entity
     */
    void Render(Renderer& p_renderer);

    /**
	 * Returns the transform component of this entity
	 */
	std::shared_ptr<TransformComponent> GetTransform() { return GetComponent<TransformComponent>(); }

    void Serialize(nlohmann::json& p_json);
	
    void Deserialize(const nlohmann::json& p_json);
                    

};

template <typename T>
bool Entity::AddComponent(std::shared_ptr<T> p_component)
{
    auto typeIndex = std::type_index(typeid(T));
    if (m_components.find(typeIndex) == m_components.end())
    {
        m_components[typeIndex] = p_component;
        p_component->owner = this;
        return true;
    }
    return false;
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent()
{
    auto typeIndex = std::type_index(typeid(T));
    auto it = m_components.find(typeIndex);
    if (it != m_components.end())
    {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return nullptr;
}
