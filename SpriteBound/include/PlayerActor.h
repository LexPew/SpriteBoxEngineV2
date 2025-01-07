#pragma once
#include "Core/ECS/SpriteComponent.h"
#include "Core/ECS/CamSys/FancyCameraComponent.h"
#include "Core/ECS/PhysicsActor.h"

//Class: PlayerActor
//Purpose: A class that represents the player in the game world with some default components, sprites and input handling setup via
//			the InputManager
class PlayerActor : public PhysicsActor
{
private:
	std::shared_ptr<SpriteComponent> spriteComponent{ nullptr };
	std::shared_ptr<FancyCameraComponent> cameraComponent{nullptr};
	std::string spriteId{ "NULL" };
public:
	PlayerActor() : PhysicsActor()
	{
		//Create a player with a NULL sprite this
		//can be set later but for now will display an error texture
		spriteId = "NULL";
	}


	
	PlayerActor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale, const std::string& p_spriteId)
		: PhysicsActor(p_name, p_position, p_scale)
	{
		spriteId = p_spriteId;
	}
	~PlayerActor()
	{
		//Remove components
		RemoveComponent(spriteComponent);
		RemoveComponent(cameraComponent);
	}
	void Awake() override;
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;

	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(cereal::base_class<PhysicsActor>(this), spriteId);
		DEBUG_LOG("PlayerActor saved with spriteId: " + spriteId);
	}
	template <class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<PhysicsActor>(this), spriteId);
		DEBUG_LOG("PlayerActor loaded with spriteId: " + spriteId);
	}

};
CEREAL_REGISTER_TYPE(PlayerActor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(PhysicsActor, PlayerActor)

