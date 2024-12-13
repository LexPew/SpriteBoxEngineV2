#pragma once
#include "Entity.h"
#include "Maths/Rect.h"


//Class: Solid
//Purpose: Extends the Entity class to include a rect for collision detection,
//			acting as a solid object in the game world that Actors can collide with.
class Solid : public Entity
{
protected:
	Rect rect; //Hold the rect of the solid used for collision detection

public:
	// Construct a new Solid object
    Solid() : Entity() {}
	/**
	 * @brief Construct a new Solid object with a name
	 * @param p_name Name of the entity
	 */
	Solid(const std::string& p_name) : Entity(p_name) {}
	/**
	 * @brief Construct a new Solid object with a name, position and scale
	 * @param p_name Name of the entity
	 * @param p_position Position of the entity
	 * @param p_scale Scale of the entity
	 */
	Solid(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale) : Entity(p_name, p_position, p_scale)
    {
		GetTransform()->SetPosition(p_position);
    }

	/**
	 * @brief Construct a new Solid object with a name, position, scale and rect
	 * @param p_name Name of the entity
	 * @param p_position Position of the entity
	 * @param p_scale Scale of the entity
	 * @param p_rect Rect of the entity
	 */
	Solid(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale, const Rect& p_rect) : Entity(p_name, p_position, p_scale), rect(p_rect)
    {
		GetTransform()->SetPosition(p_position);
    }

	//Destruct the Solid object
    ~Solid() override {}

    void Start() override;
    void Update(float p_deltaTime) override;
    void Render(Renderer& p_renderer) override;

	void Move(const Vector2& p_movement);

	/**
	 * @brief Get the rect of the solid
	 * @return Rect& The rect of the solid
	 */
	Rect& GetRect() { return rect; }

	/**
	 * @brief Set the rect of the solid
	 * @param p_rect The new rect of the solid
	 */
	void SetRect(const Rect& p_rect) { rect = p_rect; }

	//Solid Serialization

	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(cereal::base_class<Entity>(this), rect);
	}
	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<Entity>(this), rect);
	}
};
CEREAL_REGISTER_TYPE(Solid)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Entity, Solid)
