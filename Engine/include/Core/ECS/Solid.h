#pragma once
#include "Entity.h"
#include "Maths/Rect.h"

class Solid : public Entity
{

public:
    Rect solidRect;

    Solid() : Entity() {}
    Solid(const std::string& p_name) : Entity(p_name) {}
    Solid(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale) : Entity(p_name, p_position, p_scale) {}
    ~Solid() override {}

    void Start() override;
    void Update(float p_deltaTime) override;
    void Render(Renderer& p_renderer) override;

};
