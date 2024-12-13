#include "Core/ECS/Actor.h"
#include "Core/SceneManager.h"
#include "Core/SceneSerializer.h"

void Actor::Start()
{
    Entity::Start();
}

void Actor::Update(float p_deltaTime)
{
    Entity::Update(p_deltaTime);
}

void Actor::Render(Renderer& p_renderer)
{
    Entity::Render(p_renderer);
}

void Actor::MoveX(float p_moveAmount, Action& p_onCollide)
{
    float moveRemaining = std::abs(p_moveAmount);
    int direction = (p_moveAmount > 0) ? 1 : -1;
    Vector2 currentPosition = GetTransform()->GetPosition();

    while (moveRemaining > 0.0f)
    {
        float step = std::min(1.0f, moveRemaining);
        Vector2 nextPosition = currentPosition;
        nextPosition.x += direction * step;

        if (!CollideAt(SceneSerializer::instance.currentScene->GetSolids(), nextPosition))
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
    float moveRemaining = std::abs(p_moveAmount);
    int direction = (p_moveAmount > 0) ? 1 : -1;
    Vector2 currentPosition = GetTransform()->GetPosition();

    while (moveRemaining > 0.0f)
    {
        float step = std::min(1.0f, moveRemaining);
        Vector2 nextPosition = currentPosition;
        nextPosition.y += direction * step;

        if (!CollideAt(SceneSerializer::instance.currentScene->GetSolids(), nextPosition))
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

bool Actor::CollideAt(std::vector<std::shared_ptr<Solid>> p_solids, Vector2 p_position)
{
    actorRect.SetPosition(p_position + originOffset);
    for (const auto& solid : p_solids)
    {
        if (solid->solidRect.Intersects(actorRect))
        {
            return true;
        }
    }
    return false;
}
