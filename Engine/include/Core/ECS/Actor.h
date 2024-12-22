#pragma once
#include "Entity.h"
#include "Core/Action.h"
#include "Maths/Rect.h"
class Solid;

//Class: Actor
//Purpose: Extends the Entity class to include movement and simple collision detection
//			via the functions MoveX, MoveY and CollideAt.

class Actor : public Entity
{
protected:
	Rect rect; //Hold the rect of the actor used for collision detection
	Vector2 originOffset; //Hold the offset of the origin point of the actor from the top left corner
public:

	// Construct a new Actor object
	Actor() : Entity() {}

	/**
	 * @brief Construct a new Actor object with a name
	 * @param p_name Name of the entity
	 * @return Actor
	 */
	Actor(const std::string& p_name) : Entity(p_name)
	{
		AddTransform(Vector2::Zero(),Vector2::One());
	}

	/**
	 * @brief Construct a new Actor object with a name, position and scale
	 * @param p_name Name of the entity
	 * @param p_position Position of the entity
	 * @param p_scale Scale of the entity
	 * @return Actor
	 */
	Actor(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale) : Entity(p_name, p_position, p_scale)
	{
		AddTransform(p_position, p_scale);
	}

	// Destruct the Actor object
	~Actor() override {}


	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;

	/**
	 * @brief Move the actor along the X axis
	 * @param p_moveAmount Amount to move the actor
	 * @param p_onCollide Action to perform when a collision is detected
	 */
	void MoveX(float p_moveAmount, Action& p_onCollide);

	/**
	 * @brief Move the actor along the Y axis
	 * @param p_moveAmount Amount to move the actor
	 * @param p_onCollide Action to perform when a collision is detected
	 */
	void MoveY(float p_moveAmount, Action& p_onCollide);


	/**
	 * @brief Move the actor to the given position
	 * @return Rect& The rect of the actor
	 */
	Rect& GetRect() { return rect; }

	/**
	 * @brief Set the rect of the actor
	 * @param p_rect The new rect of the actor
	 */
	void SetRect(const Rect& p_rect) { rect = p_rect; }

	/**
	 * @brief Set the origin offset of the actor
	 * @return Vector2 The new origin offset of the actor
	 */
	void SetOriginOffset(const Vector2& p_offset) { originOffset = p_offset; }

protected:
	/**
	 * @brief Check if the actor collides with any solids at the given position
	 * @param p_solids List of solids to check for collision
	 * @param p_position Position to check for collision
	 * @return bool True if a collision is detected
	 */
	bool CollideAt(const std::vector<std::shared_ptr<Solid>>& p_solids, Vector2 p_position);

	/**
	* @brief Check if the actor is riding on the given solid
	* @param p_solid Solid to check if the actor is riding on
	* @return bool True if the actor is riding on the solid
	*/
	bool IsRiding(Solid p_solid) const;





	//Actor Serialization
public:
	template<class Archive>
	void save(Archive& p_archive) const
	{

		p_archive(cereal::base_class<Entity>(this), rect, originOffset);
	}
	template<class Archive>
	void load(Archive& p_archive)
	{

		p_archive(cereal::base_class<Entity>(this), rect, originOffset);
	}
};
CEREAL_REGISTER_TYPE(Actor)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, Actor)

