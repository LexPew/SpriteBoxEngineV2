#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class TransformComponent : public Component
{
private:
    Vector2 position;
	Vector2 scale;
public:

    TransformComponent() : position(Vector2::Zero()), scale(Vector2::One()) {}
    TransformComponent(const Vector2& p_position, const Vector2& p_scale) : position(p_position), scale(p_scale) {}

    void Serialize(nlohmann::json& p_json) override;

    void Deserialize(const nlohmann::json& p_json) override;

    void Start() override;

    void Update(float p_deltaTime) override;

    void Render(Renderer& p_renderer) override;


    void SetPosition(const Vector2& p_position)
    {
		position = p_position;
    }

    const Vector2& GetPosition() const
    {
        return position;
    }

    void SetScale(const Vector2& p_scale)
    {
        scale = p_scale;
    }

    const Vector2& GetScale() const
    {
        return scale;
    }
};
