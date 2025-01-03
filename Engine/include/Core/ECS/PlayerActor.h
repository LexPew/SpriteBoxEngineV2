#pragma once
#include "SpriteComponent.h"
#include "CamSys/FancyCameraComponent.h"
#include "Core/ECS/PhysicsActor.h"

//Class: PlayerActor
//Purpose: A class that represents the player in the game world with some default components, sprites and input handling setup via
//			the InputManager
class PlayerActor : public PhysicsActor
{
private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<FancyCameraComponent> cameraComponent;
public:
	PlayerActor() : PhysicsActor()
	{
		//Create a player with a NULL sprite this
		//can be set later but for now will display an error texture
		Init("NULL");
	}


	
	PlayerActor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale, const std::string& p_spriteId)
		: PhysicsActor(p_name, p_position, p_scale)
	{

		Init(p_spriteId);
	}

	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;
	void Init(const std::string& p_spriteId)
	{
		spriteComponent = std::make_shared<SpriteComponent>(p_spriteId, AssetManager::GetInstance());
		AddComponent(spriteComponent);
		cameraComponent = std::make_shared<FancyCameraComponent>(Vector2(800, 600));
		AddComponent(cameraComponent);
	}
};
CEREAL_REGISTER_TYPE(PlayerActor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(PhysicsActor, PlayerActor)

