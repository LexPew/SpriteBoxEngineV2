#include "Core/ECS/CharacterActor.h"
#include "Core/SceneManager.h"

void CharacterActor::Start()
{
	Actor::Start(); // Call base class start if necessary
    onHorizontalCollision.SetCallback([this]() {velocityX = 0; });
	onVerticalCollision.SetCallback([this]() {velocityY = 0; });
	onLand.SetCallback([this]() { });
}
void CharacterActor::Update(float p_deltaTime)
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
	isGrounded = CollideAt(SceneManager::instance.currentScene->GetSolids(), GetTransform()->GetPosition() + Vector2(0, 1));
    if(isGrounded)
    {
		jumpCount = 0;
		onLand.Invoke();
    }
}

void CharacterActor::Jump()
{
    if (!isGrounded && jumpCount == 0) return;
    if (jumpCount < maxJumps)
    {
        velocityY = jumpStrength;
        jumpCount++;
        isGrounded = false;
    }
}
