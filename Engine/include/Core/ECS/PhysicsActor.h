#pragma once
#include "Actor.h"

//Class: PhysicsActor
//Purpose: A class that represents an actor using physics in the game world
class PhysicsActor : public Actor
{
protected:
	float velocityX = 0.0f;
	float velocityY = 0.0f;
	bool isGrounded = false;
	int jumpCount = 0; 
	int maxJumps = 2;   // Maximum number of jumps

	float gravity = 500;   // Gravity strength
	float jumpStrength = -250; // Upward force for jumping
	float maxFallSpeed = 500;  // Terminal velocity 

	Action onHorizontalCollision; // Action to take on horizontal collision
	Action onVerticalCollision;   // Action to take on vertical collision
	Action onLand;                // Action to take on landing


public:
	//Constructs a PhysicsActor with default values
	PhysicsActor() : Actor() {}

	/**
	 * @brief Construct a new PhysicsActor Actor object
	 * @param p_name The name of the actor
	 * @param p_position The position of the actor
	 * @param p_scale The scale of the actor
	 */
	PhysicsActor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale)
		: Actor(p_name, p_position, p_scale) {

	}

	void Start() override;
	void Update(float p_deltaTime) override;
	void Jump();

	/**
	 * @brief Moves the actor in the x direction
	 * @param p_direction The direction to move the actor
	 */
	void SetVelocityX(float p_velocityX) { velocityX = p_velocityX; }

	/**
	 * @brief Moves the actor in the y direction
	 * @param p_direction The direction to move the actor
	 */
	void SetVelocityY(float p_velocityY) { velocityY = p_velocityY; }

	/**
	 * @brief Returns the velocity of the actor in the x direction
	 * @return float The velocity of the actor in the x direction
	 */
	float GetVelocityX() const { return velocityX; }

	/**
	 * @brief Returns the velocity of the actor in the y direction
	 * @return float The velocity of the actor in the y direction
	 */
	float GetVelocityY() const { return velocityY; }

	//More getters and setters
	void SetMaxJumps(const int p_max) { maxJumps = p_max; }
	int GetMaxJumps() const { return maxJumps; }

	void SetMaxFallSpeed(const float p_maxFallSpeed) { maxFallSpeed = p_maxFallSpeed; }
	float GetMaxFallSpeed() const { return maxFallSpeed; }

	float GetGravity() const { return gravity; }
	void SetGravity(const float p_gravity) { gravity = p_gravity; }

	void SetJumpStrength(const float p_jumpStrength) { jumpStrength = p_jumpStrength; }
	float GetJumpStrength() const { return jumpStrength; }


	// Setters for grounded state and gettters
	void SetIsGrounded(const bool p_isGrounded) { isGrounded = p_isGrounded; }
	bool IsGrounded() const { return isGrounded; }

	//SERIALIZATION

	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(cereal::base_class<Actor>(this), velocityX, velocityY, isGrounded, jumpCount, maxJumps, gravity, jumpStrength, maxFallSpeed);
	}
	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<Actor>(this), velocityX, velocityY, isGrounded, jumpCount, maxJumps, gravity, jumpStrength, maxFallSpeed);
	}

};
CEREAL_REGISTER_TYPE(PhysicsActor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Actor, PhysicsActor)

