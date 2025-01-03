#include "Core/ECS/Entity.h"

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




