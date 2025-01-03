#pragma once
#include "Core/ECS/Component.h"
#include "Maths/Vector2.h"

class UIComponent : public Component
{
public:
	UIComponent() = default;
    virtual void HandleInput(const Vector2& p_mousePosition, bool p_click) = 0;
};

CEREAL_REGISTER_TYPE(UIComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, UIComponent)
