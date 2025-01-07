#pragma once
#include "Core/ECS/Component.h"
#include "Maths/Vector2.h"

#include "ThirdParty/Event.h"


/**
 * Transform component, used to define the position and scale of an entity
 */
class TransformComponent : public Component
{
private:
    Vector2 position{0,0};
	Vector2 scale{1,1};
public:
	Event<Vector2&> onPositionChanged;
	Event<Vector2&> onScaledChanged;

    /**
	 * Creates a new transform component with default values
     */
    TransformComponent()
    {
        onPositionChanged(position);
        onScaledChanged(scale);
    }


    /**
	 * Creates a new transform component with the given position and scale
     */
    TransformComponent(const Vector2& p_position, const Vector2& p_scale) : position(p_position), scale(p_scale)
    {
        onPositionChanged(position);
        onScaledChanged(scale);
    }


  

    void Start() override;

    /**
	 * Sets the position of the entity
	 */
    void SetPosition(const Vector2& p_position)
    {
		position = p_position;
		onPositionChanged(position);
    }

    /**
	* Returns the position of the entity
	*/
    const Vector2& GetPosition() const
    {
        return position;
    }

    /**
	* Sets the scale of the entity
	*/
    void SetScale(const Vector2& p_scale)
    {
        scale = p_scale;
		onScaledChanged(scale);
    }

    /**
	 * Returns the scale of the entity
     */
    const Vector2& GetScale() const
    {
        return scale;
    }


    template <class Archive>
    void save(Archive& ar) const
    {
		ar(position, scale);
    }

    template <class Archive>
    void load(Archive& ar)
    {
		ar(position, scale);
    }
};
CEREAL_REGISTER_TYPE(TransformComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, TransformComponent)
