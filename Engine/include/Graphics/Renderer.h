#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

struct SpriteData;
struct TextData;
struct Vector2;
class Rect;


//TODO: Add support for rendering to textures

//TODO: Add support for post-processing effects

//Class: Renderer
//Purpose: Handles rendering of sprites, shapes, and text
class Renderer
{
private:
    static Renderer* instance;
    sf::RenderWindow* window;
    sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::CircleShape circle;
    sf::Text text;
    sf::Sprite backgroundSprite;
    bool backgroundSet{ false };

    Renderer() : window(nullptr) {}
    ~Renderer()
	{
		window = nullptr;
		delete instance;
    }

public:
    static Renderer& GetInstance()
    {
        if (!instance)
        {
            instance = new Renderer();
        }
        return *instance;
    }

    void SetWindow(sf::RenderWindow* p_window);
    sf::RenderWindow* GetWindow() const { return window; }

    void SetView(const sf::View& p_view) const;
    void DrawSprite(const SpriteData& p_spriteData, int p_frameIndex,
        const Vector2& p_position, const Vector2& p_scale, bool p_flipped);
    void DrawRect(const Rect& p_rect, const sf::Color& p_color);
    void DrawPoint(const Vector2& p_point, const sf::Color& p_color);

    void DrawText(const TextData& p_textData, const Vector2& p_position);
    static Vector2 GetSpriteBounds(const SpriteData& p_spriteData);

    void SetBackground(const std::string& p_textureId);
    void DrawBackground() const;
    void HandleWindowSizeUpdate();
    sf::RenderWindow* GetRenderWindow() const { return window; }
};
