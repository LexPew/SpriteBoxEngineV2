#pragma once


#include <iso646.h>

#include "Entity.h"
#include "Core/ECS/Component.h"
#include "Physics/Impulse2DLite.h"

class RigidBodyComponent : public Component
{
private:

    std::shared_ptr<RectangleBody> body;
    Vector2 originOffset;



public:
    RigidBodyComponent() : body(std::make_shared<RectangleBody>()) {}

    RigidBodyComponent(float p_mass, float p_restitution, const Rect& p_rect)
        : body(std::make_shared<RectangleBody>( Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), Vector2(0, 0), p_mass, p_restitution, 0.99f, p_rect) ){
    }
    RigidBodyComponent(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const Vector2& p_force, float p_mass, float p_restitution, float p_damping, const Rect& p_rect)
        : body(std::make_shared<RectangleBody>( p_position, p_velocity, p_acceleration, p_force, p_mass, p_restitution, p_damping, p_rect) ){
    }



    void Start() override
    {
		if (body == nullptr) return;

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
    RectangleBody& GetBody() { return *body; }

    std::shared_ptr<RectangleBody> GetBodyPtr() { return body; }
    const RectangleBody& GetBody() const { return *body; }

	template<class Archive>
	void save(Archive& p_archive) const
	{

		p_archive(cereal::base_class<Component>(this), body, originOffset);
	}

	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<Component>(this), body, originOffset);
	}

};
CEREAL_REGISTER_TYPE(RigidBodyComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component,RigidBodyComponent)
