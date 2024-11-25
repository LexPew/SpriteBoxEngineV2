#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Core/ECS/Component.h"
#include "Physics/Impulse2DLite.h"

class RigidBodyComponent : public Component
{
private:

    RectangleBody* body;
    Vector2 originOffset;

public:
    RigidBodyComponent(float p_mass, float p_restitution, const Rect& p_rect)
        : body(new RectangleBody( Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), p_mass, p_restitution, 0.99f, p_rect) ){
    }
    RigidBodyComponent(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const Vector2& p_force, float p_mass, float p_restitution, float p_damping, const Rect& p_rect)
        : body(new RectangleBody( p_position, p_velocity, p_acceleration, p_force, p_mass, p_restitution, p_damping, p_rect) ){
    }


    void Start() override
    {
		const Vector2& scale = owner->GetTransform()->GetScale();
		originOffset.x = body->GetRect().Width / 2 * scale.x;
        originOffset.y = body->GetRect().Height / 2 * scale.y;

        Rect p_scaledRect = body->GetRect();
        p_scaledRect *= scale;
		body->SetRect(p_scaledRect);
        body->SetPosition(owner->GetTransform()->GetPosition() - originOffset);
		Physics::GetInstance()->Add(body);


        
        // Initialize the rigid body component
    }

    void Update(float p_deltaTime) override
    {
		owner->GetTransform()->SetPosition(body->GetPosition() + originOffset);


    }

    void Render(Renderer& p_renderer) override
    {
        // Render the rigid body component if necessary
    }
    void DebugRender(sf::RenderWindow& window)
    {
        sf::RectangleShape rectShape;
        rectShape.setPosition(body->GetPosition().x, body->GetPosition().y);
        rectShape.setSize(sf::Vector2f(body->GetRect().Width, body->GetRect().Height));
        rectShape.setFillColor(sf::Color::Transparent);
        rectShape.setOutlineColor(sf::Color::Red);
        rectShape.setOutlineThickness(1.0f);
        window.draw(rectShape);
    }
    void Serialize(nlohmann::json& p_json) override
    {

    }

    void Deserialize(const nlohmann::json& p_json) override
    {

    }

    RectangleBody& GetBody() { return *body; }
    const RectangleBody& GetBody() const { return *body; }
};
