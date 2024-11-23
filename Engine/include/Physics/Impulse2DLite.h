#pragma once
#include "Maths/Vector2.h"
#include "Maths/Rect.h"

class Body
{
protected:
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float inverseMass;
	float restitution;
	float damping;


public:
	Body() : position(Vector2::Zero()), velocity(Vector2::Zero()), acceleration(Vector2::Zero()), force(Vector2::Zero()), inverseMass(0), restitution(0), damping(1) {}
	Body(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const Vector2& p_force, const float p_mass, const float p_restitution, const float p_damping)
	: position(p_position), velocity(p_velocity), acceleration(p_acceleration), force(p_force), inverseMass(1.0f / p_mass), restitution(p_restitution), damping(p_damping) {}

	void ApplyForce(Vector2 p_force)
	{
		force += p_force;
	}
	virtual void Integrate(float p_deltaTime)
	{
		//Object is static
		if (inverseMass <= 0)
		{
			return;
		}
		acceleration = force * inverseMass;
		velocity += acceleration * p_deltaTime;
		position += velocity * p_deltaTime;
		force.Clear();
		velocity *= damping;

	}


	const Vector2& GetPosition() const { return position; }
	const Vector2& GetVelocity() const { return velocity; }
	const Vector2& GetAcceleration() const { return acceleration; }
	const Vector2& GetForce() const { return force; }
	float GetMass() const
	{
		if(!IsStatic())
		{
			return 1.0f / inverseMass;
		}
		return 0;
	}
	float GetInverseMass() const { return inverseMass; }
	float GetRestitution() const { return restitution; }
	float GetDamping() const { return damping; }
	bool IsStatic() const { return inverseMass <= 0; }
	virtual void SetPosition(const Vector2& p_position) { position = p_position; }
	void SetVelocity(const Vector2& p_velocity) { velocity = p_velocity; }
	void SetAcceleration(const Vector2& p_acceleration) { acceleration = p_acceleration; }
	void SetForce(const Vector2& p_force) { force = p_force; }
	void SetMass(const float p_mass)
	{
		if(p_mass > 0)
		{
		inverseMass = 1.0f / p_mass;
		}
		else
		{
			inverseMass = 0;
		}
	}
	void SetRestitution(const float p_restitution) { restitution = p_restitution; }
	void SetDamping(const float p_damping) { damping = p_damping; }

};

class RectangleBody : public Body
{
private:
	Rect rect;
public:
	RectangleBody() : rect(Rect()) {}
	RectangleBody(const Vector2& p_position, const Vector2& p_velocity, const Vector2& p_acceleration, const Vector2& p_force, const float p_mass, const float p_restitution, const float p_damping, const Rect& p_rect)
		: Body(p_position, p_velocity, p_acceleration, p_force, p_mass, p_restitution, p_damping), rect(p_rect) {
	}
	const Rect& GetRect() const { return rect; }
	void SetRect(const Rect& p_rect) { rect = p_rect; }


	void SetPosition(const Vector2& p_position) override
	{
		Body::SetPosition(p_position);
		rect.SetPosition(p_position);
	}

	void Integrate(float p_deltaTime) override
	{
		Body::Integrate(p_deltaTime);
		rect.SetPosition(position);
	}
};

class Physics
{
private:
	inline static Physics* instance;
	std::vector<RectangleBody*> m_bodies;
	Vector2 gravity;

public:
	Physics() : gravity(Vector2(0,-2000.0f))
	{
		instance = this;
	}
	Physics(const Vector2& p_gravity) : gravity(p_gravity)
	{
		instance = this;
	}

	static Physics* GetInstance()
	{
		if (!instance)
		{
			instance = new Physics();
		}
		return instance;
	}
	void Add(RectangleBody* p_body)
	{
		m_bodies.push_back(p_body);

	}
	void SetGravity(const Vector2& p_gravity)
	{
		gravity = p_gravity;
	}
	void ResolveCollision(RectangleBody* p_bodyA, RectangleBody* p_bodyB, const Vector2& p_penetration)
	{
		Vector2 penetrationOverlap = p_penetration;
		Vector2 collisionNormal;

		if (std::abs(p_penetration.x) < std::abs(p_penetration.y)) // X-axis resolution
		{
			collisionNormal = { p_penetration.x < 0 ? -1.0f : 1.0f, 0 };
		}
		else // Y-axis resolution
		{
			collisionNormal = { 0, p_penetration.y < 0 ? -1.0f : 1.0f };
		}

		// Resolve overlap symmetrically
		if (!p_bodyA->IsStatic() && !p_bodyB->IsStatic())
		{
			p_bodyA->SetPosition(p_bodyA->GetPosition() + penetrationOverlap * 0.5f);
			p_bodyB->SetPosition(p_bodyB->GetPosition() - penetrationOverlap * 0.5f);
		}
		else if (!p_bodyA->IsStatic())
		{
			p_bodyA->SetPosition(p_bodyA->GetPosition() + penetrationOverlap);
		}
		else if (!p_bodyB->IsStatic())
		{
			p_bodyB->SetPosition(p_bodyB->GetPosition() - penetrationOverlap);
		}

		// Calculate relative velocity
		Vector2 relativeVelocity = p_bodyB->GetVelocity() - p_bodyA->GetVelocity();

		// Calculate relative velocity in terms of the normal direction
		float velocityAlongNormal = relativeVelocity * collisionNormal;

		// Do not resolve if velocities are separating
		if (velocityAlongNormal > 0)
			return;

		// Calculate restitution
		float e = std::min(p_bodyA->GetRestitution(), p_bodyB->GetRestitution());

		// Calculate impulse scalar
		float j = -(1 + e) * velocityAlongNormal;
		j /= p_bodyA->GetInverseMass() + p_bodyB->GetInverseMass();

		// Apply impulse
		const Vector2 impulse = collisionNormal * j;
		if (!p_bodyA->IsStatic())
		{
			p_bodyA->SetVelocity(p_bodyA->GetVelocity() - impulse * p_bodyA->GetInverseMass());
		}
		if (!p_bodyB->IsStatic())
		{
			p_bodyB->SetVelocity(p_bodyB->GetVelocity() + impulse * p_bodyB->GetInverseMass());
		}
	}
	void CheckCollision(RectangleBody* p_bodyA, RectangleBody* p_bodyB)
	{
		//Check if the two rectangles are intersecting
		if(p_bodyA->GetRect().Intersects(p_bodyB->GetRect()))
		{
			const Vector2 penetration = p_bodyA->GetRect().CalculatePenetration(p_bodyB->GetRect());

			//If there is a penetration lol
			if (penetration.x != 0 || penetration.y != 0)
			{
				ResolveCollision(p_bodyA, p_bodyB, penetration);
			}
		}
	}

	void Update(float p_deltaTime)
	{
		for (RectangleBody* body : m_bodies)
		{
			body->ApplyForce(gravity);
			body->Integrate(p_deltaTime);

		}
		for (size_t i = 0; i < m_bodies.size(); i++)
		{
			for (size_t j = i + 1; j < m_bodies.size(); j++)
			{
				CheckCollision(m_bodies[i], m_bodies[j]);
			}
		}
	}
};
