#include "PlayerActor.h"

#include "Core/InputManager.h"
#include "Graphics/Renderer.h"

void PlayerActor::Awake()
{

	PhysicsActor::Awake();
	if (!spriteComponent)
	{
		spriteComponent = std::make_shared<SpriteComponent>(spriteId, AssetManager::GetInstance());
		AddComponent(spriteComponent);
	}
	if (!cameraComponent) 
	{
		cameraComponent = std::make_shared<FancyCameraComponent>(Vector2(800, 600));
		AddComponent(cameraComponent);
	}

	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::A);
	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::D);
	InputManager::GetInstance().RegisterKey(sf::Keyboard::Key::W);

	//Setup rect
	const Vector2 spriteBounds = Renderer::GetInstance().GetSpriteBounds(GetComponent<SpriteComponent>()->sprite.GetSpriteData());
	SetOriginOffset({ -spriteBounds.x / 2.0f, -spriteBounds.y / 2.0f });
	SetRect({ 0,0,spriteBounds.y, spriteBounds.x });
}

void PlayerActor::Start()
{
	PhysicsActor::Start();
	cameraComponent->ZoomToFactor(.6f);


}

void PlayerActor::Update(float p_deltaTime)
{
	PhysicsActor::Update(p_deltaTime);
	if (InputManager::GetInstance().IsPressed(sf::Keyboard::Key::W))
	{
		Jump();
	}
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
	//TODO: Fix camera zooming with parallax backgrounds
	//Handle zooming
	//cameraComponent->ZoomToFactor(InputManager::GetInstance().GetScrollWheelDelta());

	//Update parallax to follow the player
	Renderer::GetInstance().UpdateBackgroundPosition({ velocityX * 0.0001f, 0});
}

void PlayerActor::Render(Renderer& p_renderer)
{
	PhysicsActor::Render(p_renderer);
	DEBUG_DRAW_POINT(p_renderer, GetTransform()->GetPosition(), sf::Color::Red);

}

