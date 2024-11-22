#pragma once
#include "Core/ECS/Component.h"
#include "Maths/Vector2.h"

/**
 * Transform component, used to define the position and scale of an entity
 */
class TransformComponent : public Component
{
private:
    Vector2 position;
	Vector2 scale;
public:

    /**
	 * Creates a new transform component with default values
     */
    TransformComponent() : position(Vector2::Zero()), scale(Vector2::One()) {}


    /**
	 * Creates a new transform component with the given position and scale
     */
    TransformComponent(const Vector2& p_position, const Vector2& p_scale) : position(p_position), scale(p_scale) {}

  

    void Start() override;

    void Update(float p_deltaTime) override;

    void Render(Renderer& p_renderer) override;

    /**
	 * Sets the position of the entity
	 */
    void SetPosition(const Vector2& p_position)
    {
		position = p_position;
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
    }

    /**
	 * Returns the scale of the entity
     */
    const Vector2& GetScale() const
    {
        return scale;
    }

    void Serialize(nlohmann::json& p_json) override;

    void Deserialize(const nlohmann::json& p_json) override;
};
