#include "Core/ECS/Solid.h"

#include <SFML/Graphics/Color.hpp>

#include "Core/SceneManager.h"
#include "Debug/DebugMacros.h"
#include "Graphics/Renderer.h"
#include "Core/ECS/Actor.h"

void Solid::OnPositionUpdated(Vector2& p_position)
{
	rect.SetPosition(p_position);
}

Solid::~Solid()
{
	//Remove position changed event

	
	actorsInTrigger.clear();
}

void Solid::Awake()
{
	Entity::Awake();
	//Add position changed event
	GetTransform()->onPositionChanged.Bind(&Solid::OnPositionUpdated, this);


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

void Solid::TriggerEntry(Actor* p_actor)
{

	//Check if the actor is already in the list if not add it
	if (std::find(actorsInTrigger.begin(), actorsInTrigger.end(), p_actor) == actorsInTrigger.end())
	{
		actorsInTrigger.push_back(p_actor);
		DEBUG_LOG("Solid: " + name + " triggered entered by actor: " + p_actor->GetName());
		onTriggerEnter(*p_actor);
	}


}




void Solid::TriggerExit(Actor* p_actor)
{

	//Check if the actor is in the list if so remove it
	auto it = std::find(actorsInTrigger.begin(), actorsInTrigger.end(), p_actor);
	if (it != actorsInTrigger.end())
	{
		DEBUG_LOG("Solid: " + name + " triggered exited by actor: " + p_actor->GetName());
		actorsInTrigger.erase(it);
		onTriggerExit(*p_actor);
	}

}
