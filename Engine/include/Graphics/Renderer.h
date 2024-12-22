#pragma once
#include <SFML/Graphics.hpp>
#include "Core/SpriteData.h"
#include "Maths/Vector2.h"

#include "Maths/Rect.h"

class Renderer
{
public:
    static Renderer* instance;
private:
    
    sf::RenderWindow* window;
	sf::Sprite sprite;
	sf::RectangleShape rect;
	sf::CircleShape circle;
public:
    Renderer(sf::RenderWindow* p_window) : window(p_window)
    {
		if (instance == nullptr)
		{
			instance = this;
		}
    };

    void SetView(const sf::View& p_view);
    void DrawSprite(const SpriteData& p_spriteData,  const int p_frameIndex,
        const Vector2& p_position, const Vector2& p_scale, bool p_flipped);
	void DrawRect(const Rect& p_rect, const sf::Color& p_color);
	void DrawPoint(const Vector2& p_point, const sf::Color& p_color);
    Vector2 GetSpriteBounds(const SpriteData& p_spriteData);

	sf::RenderWindow* GetWindow() { return window; }
};
