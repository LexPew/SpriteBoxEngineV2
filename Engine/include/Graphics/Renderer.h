#pragma once
#include <SFML/Graphics.hpp>
#include "Core/SpriteData.h"
#include "Maths/Vector2.h"

class Renderer
{
private:
    sf::RenderWindow* window;

public:
    Renderer(sf::RenderWindow* p_window) : window(p_window) {};

    void DrawSprite(const SpriteData& p_spriteData,  const int p_frameIndex, const Vector2& p_position, const Vector2& p_scale);
};
