#include "Core/ECS/PlayerActor.h"

#include "Core/InputManager.h"
#include "Graphics/Renderer.h"

void PlayerActor::Start()
{
	PhysicsActor::Start();
	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::A);
	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::D);
	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::W);

	//Setup rect
	const Vector2 spriteBounds = Renderer::GetInstance().GetSpriteBounds(GetComponent<SpriteComponent>()->sprite.GetSpriteData());
	SetOriginOffset({ -spriteBounds.x / 2.0f, -spriteBounds.y / 2.0f });
	SetRect({ 0,0,spriteBounds.y, spriteBounds.x });

}

void PlayerActor::Update(float p_deltaTime)
{
	PhysicsActor::Update(p_deltaTime);

	if (InputManager::GetInstance().IsHeld(sf::Keyboard::Key::A))
	{
		SetVelocityX(-150);
		spriteComponent->Flip(true);
	}
	else if (InputManager::GetInstance().IsHeld(sf::Keyboard::Key::D))
	{
		SetVelocityX(150);
		spriteComponent->Flip(false);
	}
	else
	{
		SetVelocityX(0);
	}
	if (InputManager::GetInstance().IsPressed(sf::Keyboard::Key::W))
	{
		Jump();
	}
	

	//Handle animations
	if (!IsGrounded())
	{
		spriteComponent->PlayAnimation("Jump");
	}
	else if (GetVelocityX() != 0)
	{
		spriteComponent->PlayAnimation("Walk");
	}
	else
	{
		spriteComponent->PlayAnimation("Idle");
	}
}

void PlayerActor::Render(Renderer& p_renderer)
{
	PhysicsActor::Render(p_renderer);
	DEBUG_DRAW_POINT(p_renderer, GetTransform()->GetPosition(), sf::Color::Red);
}

