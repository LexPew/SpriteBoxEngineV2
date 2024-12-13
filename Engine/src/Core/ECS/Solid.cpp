#include "Core/ECS/Solid.h"

void Solid::Start()
{
	Entity::Start();
	solidRect.SetPosition(GetTransform()->GetPosition());
	std::cout << "Solid Start" << std::endl;
	std::cout << "Solid Position: " << GetTransform()->GetPosition().x << ", " << GetTransform()->GetPosition().y << std::endl;
}
void Solid::Update(float p_deltaTime)
{
	Entity::Update(p_deltaTime);
	solidRect.SetPosition(GetTransform()->GetPosition());
}
void Solid::Render(Renderer& p_renderer)
{
	Entity::Render(p_renderer);
}