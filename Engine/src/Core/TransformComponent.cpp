#include "Core/TransformComponent.h"

#include <iostream>

void TransformComponent::Serialize(nlohmann::json& p_json)
{
    p_json = nlohmann::json{ {"type", "TransformComponent"}, {"position", position}, {"scale", scale} };
    std::cout << "Serialized position: (" << position.x << ", " << position.y << "), scale: (" << scale.x << ", " << scale.y << ")\n";
}

void TransformComponent::Deserialize(const nlohmann::json& p_json)
{
    p_json.at("position").get_to(position);
    p_json.at("scale").get_to(scale);
    std::cout << "Deserialized position: (" << position.x << ", " << position.y << "), scale: (" << scale.x << ", " << scale.y << ")\n";
}

void TransformComponent::Start()
{
	//Start stuff
}

void TransformComponent::Update(float p_deltaTime)
{
	//Update stuff
}

void TransformComponent::Render(Renderer& p_renderer)
{
	//Render stuff
}
