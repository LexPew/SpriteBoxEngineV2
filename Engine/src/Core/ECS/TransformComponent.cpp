#include "Core/ECS/TransformComponent.h"

#include <iostream>



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

void TransformComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{ {"type", "TransformComponent"}, {"position", position}, {"scale", scale} };
}

void TransformComponent::Deserialize(const nlohmann::json& p_json)
{
	p_json.at("position").get_to(position);
	p_json.at("scale").get_to(scale);
}
