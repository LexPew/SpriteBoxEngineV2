#pragma once

//CEREAL
#include "cereal/types/memory.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/polymorphic.hpp"

//NORMAL
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <memory>

#include "Debug/DebugMacros.h"
#include "Maths/Vector2.h"


struct SpriteData;
struct TextData;
class Rect;

//Struct: BackgroundLayer
//Purpose: Represents a single layer of a parallax scrolling background, or a static background
struct BackgroundLayer
{
    BackgroundLayer() = default;
    sf::Sprite sprite; //Background sprite
	std::string textureId{"NULL"}; //Id of the texture used for the background
	float parallaxFactor{1.0f}; //Determines how much the background moves relative to the target position

    template <class Archive>
    void serialize(Archive& p_archive)
    {
        p_archive(textureId, parallaxFactor);
        DEBUG_LOG("Serialized background layer");
    }
};




//TODO: Add support for rendering to textures

//TODO: Add support for post-processing effects

//DONE: Add support for parallax scrolling backgrounds

//Class: Renderer
//Purpose: Handles rendering of sprites, shapes, and text
class Renderer
{
private:
    static Renderer* instance;
    sf::RenderWindow* window{nullptr};
    sf::Sprite sprite;
    sf::RectangleShape rect;
    sf::CircleShape circle;
    sf::Text text;


	std::vector<BackgroundLayer> backgroundLayers;
    Vector2 backgroundPosition;
    Renderer() = default;
    ~Renderer()
	{
		window = nullptr;
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
	Vector2 GetTextSize(const TextData& p_textData);

    static Vector2 GetSpriteBounds(const SpriteData& p_spriteData);
	Vector2 GetSpriteBounds(const std::string& p_spriteId);
	//Background rendering
    void AddBackgroundLayer(const std::string& p_textureId, const float p_parallaxFactor);
    void UpdateBackgroundPosition(const Vector2& p_velocity);
	void SetBackGroundPosition(const Vector2& p_position);
    void DrawBackground();


    void HandleWindowSizeUpdate();

    template <class Archive>
    void save(Archive& p_archive) const
    {
        p_archive(backgroundLayers, backgroundPosition);
		DEBUG_LOG("Saved renderer");
    }

    template <class Archive>
    void load(Archive& p_archive)
    {
        std::vector<BackgroundLayer> backgroundLayersTemp;
        p_archive(backgroundLayersTemp, backgroundPosition);
        for (auto& layer : backgroundLayersTemp)
        {
            AddBackgroundLayer(layer.textureId, layer.parallaxFactor);
        }
		DEBUG_LOG("Loaded renderer");
    }
};


