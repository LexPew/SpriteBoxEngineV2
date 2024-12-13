#include "Core/ECS/Actor.h"
#include "Core/SceneManager.h"


void Actor::Start()
{
    Entity::Start();
    DEBUG_LOG("Actor: " << name << " started");
    rect.SetPosition(GetTransform()->GetPosition());

}

void Actor::Update(float p_deltaTime)
{
    Entity::Update(p_deltaTime);
}

void Actor::Render(Renderer& p_renderer)
{
    Entity::Render(p_renderer);
	DEBUG_DRAW_RECT(p_renderer, rect, DEBUG_STGREEN);
}

void Actor::MoveX(float p_moveAmount, Action& p_onCollide)
{
    // Calculate the amount of movement remaining and the direction
    float moveRemaining = std::abs(p_moveAmount);
    int direction = (p_moveAmount > 0) ? 1 : -1;
    Vector2 currentPosition = GetTransform()->GetPosition();

    while (moveRemaining > 0.0f)
    {
        float step = std::min(1.0f, moveRemaining);
        Vector2 nextPosition = currentPosition;
        nextPosition.x += direction * step;

        if (!CollideAt(SceneManager::instance.currentScene->GetSolids(), nextPosition))
        {
            currentPosition.x = nextPosition.x;
            moveRemaining -= step;
        }
        else
        {
            // Collision detected, invoke the collision action
            p_onCollide.Invoke();
            break;
        }
    }

    GetTransform()->SetPosition(currentPosition);
}

void Actor::MoveY(float p_moveAmount, Action& p_onCollide)
{
	// Calculate the amount of movement remaining and the direction
    float moveRemaining = std::abs(p_moveAmount);
    int direction = (p_moveAmount > 0) ? 1 : -1;
    Vector2 currentPosition = GetTransform()->GetPosition();

    while (moveRemaining > 0.0f)
    {
        float step = std::min(1.0f, moveRemaining);
        Vector2 nextPosition = currentPosition;
        nextPosition.y += direction * step;

        if (!CollideAt(SceneManager::instance.currentScene->GetSolids(), nextPosition))
        {
            currentPosition.y = nextPosition.y;
            moveRemaining -= step;
        }
        else
        {
            // Collision detected, invoke the collision action
            p_onCollide.Invoke();
            break;
        }
    }

    GetTransform()->SetPosition(currentPosition);
}

bool Actor::CollideAt(std::vector<std::shared_ptr<Solid>>& p_solids, Vector2 p_position)
{
    rect.SetPosition(p_position + originOffset);
    for (const auto& solid : p_solids)
    {
        if (solid->GetRect().Intersects(rect))
        {
			//Commented out for now as it is not needed and gets annoying
			//DEBUG_LOG("Collision detected between Actor: " << name << " and Solid: " << solid->GetName());
            return true;
        }
    }
    return false;
}

bool Actor::IsRiding(Solid p_solid) const
{
	return rect.Bottom == p_solid.GetRect().Top;
}
