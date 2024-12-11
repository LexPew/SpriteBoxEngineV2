#include "Core/ECS/Entity.h"
#include "Core/AssetManager.h"
#include "Core/ECS/RigidBodyComponent.h"
#include "Core/ECS/CamSys/FancyCameraComponent.h"
#include "Core/ECS/CamSys/RawCameraComponent.h"
#include "Core/ECS/SpriteComponent.h"

void Entity::AddTransform(const Vector2& p_position, const Vector2& p_scale)
{
	// Add a TransformComponent by default
	AddComponent(std::make_shared<TransformComponent>(p_position, p_scale));
}

void Entity::Start()
{
	for (auto& pair : m_components)
	{
		pair.second->Start();
	}
}

void Entity::Update(float p_deltaTime)
{
	for (auto& pair : m_components)
	{
		pair.second->Update(p_deltaTime);
	}
}

void Entity::Render(Renderer& p_renderer)
{
	for (auto& pair : m_components)
	{
		pair.second->Render(p_renderer);
	}
}

void Entity::Serialize(nlohmann::json& p_json)
{
	p_json["name"] = name;
	p_json["active"] = active;
	p_json["components"] = nlohmann::json::array();
	for (auto& pair : m_components)
	{
		nlohmann::json componentJson;
		pair.second->Serialize(componentJson);
		p_json["components"].push_back(componentJson);
	}
}

void Entity::Deserialize(const nlohmann::json& p_json)
{
    p_json.at("name").get_to(name);
    p_json.at("active").get_to(active);
    for (const auto& component_json : p_json.at("components"))
    {
        std::string type = component_json.at("type").get<std::string>();
        if (type == "TransformComponent")
        {
            GetTransform()->Deserialize(component_json);
        }
        else if (type == "SpriteComponent")
        {
            auto sprite = std::make_shared<SpriteComponent>("Adventurer", AssetManager::GetInstance());
            sprite->Deserialize(component_json);
            AddComponent(sprite);
        }
        else if (type == "RawCameraComponent")
        {
            auto camera = std::make_shared<RawCameraComponent>();
            camera->Deserialize(component_json);
            AddComponent(camera);
        }
        else if (type == "FancyCameraComponent")
        {
            auto fancyCamera = std::make_shared<FancyCameraComponent>();
            fancyCamera->Deserialize(component_json);
            AddComponent(fancyCamera);
        }
        else if(type == "RigidBodyComponent")
        {
            auto rigidbodyComponent = std::make_shared<RigidBodyComponent>();
            rigidbodyComponent->Deserialize(component_json);
            AddComponent(rigidbodyComponent);
        }
        // Add other component types here future me
    }
}

