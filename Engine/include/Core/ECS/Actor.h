#pragma once
#include "Entity.h"
#include "Core/Action.h"
#include "Maths/Rect.h"
class Solid;

class Actor : public Entity
{
protected:
	Rect actorRect;
	Vector2 originOffset;
public:
	Actor() : Entity() {}
	Actor(const std::string& p_name) : Entity(p_name)
	{
		AddTransform(Vector2::Zero(),Vector2::One());
	}
	Actor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale) : Entity(p_name, p_position, p_scale)
	{
		AddTransform(p_position, p_scale);
	}
	~Actor() override {}
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;

	//----------ACTOR MOVEMENT----------

	void MoveX(float p_moveAmount, Action& p_onCollide);
	void MoveY(float p_moveAmount, Action& p_onCollide);
	const Rect& GetRect() const { return actorRect; }
	Rect& GetRect() { return actorRect; }
	void SetRect(const Rect& p_rect) { actorRect = p_rect; }
	void SetOriginOffset(const Vector2& p_offset) { originOffset = p_offset; }
protected:
	bool CollideAt(std::vector<std::shared_ptr<Solid>> p_solids, Vector2 p_position);
	bool IsRiding(Solid solid);






	//---------ACTOR SERIALIZATION---------
public:
	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(cereal::base_class<Entity>(this), actorRect);
	}
	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<Entity>(this), actorRect);
	}
};
CEREAL_REGISTER_TYPE(Actor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, Actor)

