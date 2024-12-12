#include "Core/ECS/SpriteComponent.h"
#include "Core/Sprite.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/TransformComponent.h"
#include "Graphics/Renderer.h"




void SpriteComponent::Start()
{
	//Do start stuff
}

void SpriteComponent::Update(float p_deltaTime)
{
	sprite.PlayAnimation(currentAnimation, p_deltaTime);
}

void SpriteComponent::Render(Renderer& p_renderer)
{
	auto transform = owner->GetTransform();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	p_renderer.DrawSprite(sprite.GetSpriteData(), sprite.GetCurrentFrame(), position, scale, flipped);
}


