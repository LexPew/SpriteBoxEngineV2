#pragma once
#include "Actor.h"
class CharacterActor : public Actor
{
private:
	float velocityX = 0.0f;  // Horizontal velocity
	float velocityY = 0.0f;  // Vertical velocity
	bool isGrounded = false; // Is the character on the ground?
	int jumpCount = 0;       // Number of jumps made
	int maxJumps = 2;   // Maximum number of jumps

	float gravity = 500;   // Gravity strength
	float jumpStrength = -250; // Upward force for jumping
	float maxFallSpeed = 500;  // Terminal velocity 

	Action onHorizontalCollision; // Action to take on horizontal collision
	Action onVerticalCollision;   // Action to take on vertical collision
	Action onLand;                // Action to take on landing


public:
	CharacterActor() : Actor() {}
	CharacterActor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale)
		: Actor(p_name, p_position, p_scale) {
	}

	void Start() override;
	void Update(float p_deltaTime) override;
	void Jump();
	//

	// Setters for velocity (if needed for additional gameplay mechanics such as movement)
	void SetVelocityX(float p_velocityX) { velocityX = p_velocityX; }
	void SetVelocityY(float p_velocityY) { velocityY = p_velocityY; }

	// Getters for velocity
	float GetVelocityX() const { return velocityX; }
	float GetVelocityY() const { return velocityY; }

	//Setter and getters for other variables
	void SetMaxJumps(const int p_max) { maxJumps = p_max; }
	int GetMaxJumps() const { return maxJumps; }
	float GetGravity() const { return gravity; }
	float GetJumpStrength() const { return jumpStrength; }
	float GetMaxFallSpeed() const { return maxFallSpeed; }
	void SetGravity(const float p_gravity) { gravity = p_gravity; }
	void SetJumpStrength(const float p_jumpStrength) { jumpStrength = p_jumpStrength; }
	void SetMaxFallSpeed(const float p_maxFallSpeed) { maxFallSpeed = p_maxFallSpeed; }

	// Setters for grounded state and gettters
	void SetIsGrounded(bool p_isGrounded) { isGrounded = p_isGrounded; }
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
CEREAL_REGISTER_TYPE(CharacterActor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Actor, CharacterActor)

