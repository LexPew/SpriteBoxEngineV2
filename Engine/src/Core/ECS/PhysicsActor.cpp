#include "Core/ECS/PhysicsActor.h"

#include "Core/InputManager.h"
#include "Core/SceneManager.h"

void PhysicsActor::Start()
{
	Actor::Start(); // Call base class start if necessary
    onHorizontalCollision.SetCallback([this]() {std::cout << "Hit a wall";  velocityX = 0; });
    onVerticalCollision.SetCallback([this]() {std::cout << "Hit vertical"; velocityY = 0; });
	onLand.SetCallback([this]() { });
}

void PhysicsActor::Update(float p_deltaTime)
{
    Actor::Update(p_deltaTime); // Call base class update if necessary

    // Apply gravity if not grounded
    if (!isGrounded)
    {
        velocityY += gravity * p_deltaTime;
        velocityY = std::min(velocityY, maxFallSpeed); // Clamp fall speed
    }

    // Calculate movement amounts
    float moveX = velocityX * p_deltaTime;
    float moveY = velocityY * p_deltaTime;


    // Horizontal movement with collision action
    MoveX(moveX, onHorizontalCollision);

	// Vertical movement with collision action
	MoveY(moveY, onVerticalCollision);

	// Check if the character is grounded
	isGrounded = CollideAt(SceneManager::GetInstance().GetCurrentScene()->GetSolids(), GetTransform()->GetPosition() + Vector2(0, 1));
	if (isGrounded && velocityY > 0)
    {
        DEBUG_LOG("Hi");
		jumpCount = 0;
		onLand.Invoke();
    }
}

void PhysicsActor::Jump()
{

    if (!isGrounded && jumpCount == 0) return;
    if (jumpCount < maxJumps)
    {
		DEBUG_LOG("Jumping");
		DEBUG_LOG(jumpCount);
        velocityY = jumpStrength;
        jumpCount += 1;
        isGrounded = false;
    }
}
