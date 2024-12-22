#include "Core/ECS/Solid.h"

#include <SFML/Graphics/Color.hpp>

#include "Core/SceneManager.h"
#include "Debug/DebugMacros.h"
#include "Graphics/Renderer.h"

void Solid::Start()
{
	Entity::Start();
	const Vector2& position = GetTransform()->GetPosition();
	rect.SetPosition(position);

}
void Solid::Update(float p_deltaTime)
{
	Entity::Update(p_deltaTime);

}
void Solid::Render(Renderer& p_renderer)
{
	Entity::Render(p_renderer);
	DEBUG_DRAW_RECT(p_renderer, rect, DEBUG_STGREEN);

}

void Solid::Move(const Vector2& p_movement)
{
	//TODO: Implement Movement for solids (static objects)
}
