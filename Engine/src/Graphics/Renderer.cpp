#include "Graphics/Renderer.h"
#include "Core/AssetManager.h"
#include "Debug/DebugMacros.h"
#include "Core/SpriteData.h"
#include "Core/ECS/UI/TextData.h"
#include "Maths/Vector2.h"
#include "Maths/Rect.h"

// Initialize the static member
Renderer* Renderer::instance = nullptr;

void Renderer::SetWindow(sf::RenderWindow* p_window)
{
    window = p_window;
}

void Renderer::SetView(const sf::View& p_view) const
{
    window->setView(p_view);
}

void Renderer::DrawSprite(const SpriteData& p_spriteData, int p_frameIndex,
    const Vector2& p_position, const Vector2& p_scale, bool p_flipped)
{
    sprite.setTexture(p_spriteData.texture);

    const int frameWidth = p_spriteData.texture.getSize().x / p_spriteData.spriteSheetColumns;
    const int frameHeight = p_spriteData.texture.getSize().y / p_spriteData.spriteSheetRows;

    // Calculate texture rect for the current frame
    const int column = p_frameIndex % p_spriteData.spriteSheetColumns;
    const int row = p_frameIndex / p_spriteData.spriteSheetColumns;

    sprite.setTextureRect(sf::IntRect(
        column * frameWidth,
        row * frameHeight,
        frameWidth,
        frameHeight
    ));
    // Set the origin to the center of the sprite
    sprite.setOrigin(frameWidth / 2.0f, frameHeight / 2.0f);
    if (p_flipped)
    {
        sprite.setScale(-p_scale.x, p_scale.y);
    }
    else
    {
        sprite.setScale(p_scale.x, p_scale.y);
    }
    sprite.setPosition(p_position.x, p_position.y);
    window->draw(sprite);
}

void Renderer::DrawRect(const Rect& p_rect, const sf::Color& p_color)
{
    rect.setSize({ p_rect.Width, p_rect.Height });
    rect.setPosition(p_rect.Left, p_rect.Top);
    rect.setFillColor(p_color);
    window->draw(rect);
}

void Renderer::DrawPoint(const Vector2& p_point, const sf::Color& p_color)
{
    circle.setRadius(1);
    circle.setPosition(p_point.x, p_point.y);
    circle.setFillColor(p_color);
    window->draw(circle);
}

void Renderer::DrawText(const TextData& p_textData, const Vector2& p_position)
{
    text.setString(p_textData.text);
    text.setCharacterSize(p_textData.fontSize);

    sf::Color color;
    color.r = p_textData.color.r;
    color.g = p_textData.color.g;
    color.b = p_textData.color.b;
    color.a = p_textData.color.a;

    text.setFillColor(color);
    text.setPosition(p_position.x, p_position.y);
    text.setFont(AssetManager::GetInstance().GetFont(p_textData.fontId));
    window->draw(text);
}

Vector2 Renderer::GetSpriteBounds(const SpriteData& p_spriteData)
{
    float frameWidth = p_spriteData.texture.getSize().x / p_spriteData.spriteSheetColumns;
    float frameHeight = p_spriteData.texture.getSize().y / p_spriteData.spriteSheetRows;
    DEBUG_LOG(p_spriteData.id << " sprite bounds: " << frameWidth << "," << frameHeight);
    return Vector2{ frameWidth, frameHeight };
}

void Renderer::SetBackground(const std::string& p_textureId)
{
    const sf::Texture& texture = AssetManager::GetInstance().GetTexture(p_textureId);
    backgroundSprite.setTexture(texture);
    backgroundSet = true;
    HandleWindowSizeUpdate();
}

void Renderer::DrawBackground() const
{
    if (backgroundSet)
    {
        window->draw(backgroundSprite);
    }
}

void Renderer::HandleWindowSizeUpdate()
{
    if (backgroundSet)
    {
        // Scale texture to window size
        sf::Vector2u windowSize = window->getSize();
        sf::Vector2u textureSize = backgroundSprite.getTexture()->getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }
}
