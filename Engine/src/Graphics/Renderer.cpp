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

Vector2 Renderer::GetTextSize(const TextData& p_textData)
{
    text.setString(p_textData.text);
	text.setCharacterSize(p_textData.fontSize);
	text.setFont(AssetManager::GetInstance().GetFont(p_textData.fontId));
	Vector2 textSize = Vector2{ text.getGlobalBounds().width, text.getGlobalBounds().height };
    return textSize;
}

Vector2 Renderer::GetSpriteBounds(const SpriteData& p_spriteData)
{
    float frameWidth = p_spriteData.texture.getSize().x / p_spriteData.spriteSheetColumns;
    float frameHeight = p_spriteData.texture.getSize().y / p_spriteData.spriteSheetRows;
    DEBUG_LOG(p_spriteData.id << " sprite bounds: " << frameWidth << "," << frameHeight);
    return Vector2{ frameWidth, frameHeight };
}



void Renderer::AddBackgroundLayer(const std::string& p_textureId, const float p_parallaxFactor)
{
    BackgroundLayer layer;

	sf::Texture& texture = AssetManager::GetInstance().GetTexture(p_textureId);
	texture.setRepeated(true);
    layer.textureId = p_textureId;
    layer.sprite.setTexture(texture);
    layer.parallaxFactor = p_parallaxFactor;

	//Set origin to the center of the texture
	sf::Vector2u textureSize = texture.getSize();

    backgroundLayers.push_back(layer);

	// Set the scale of the background layer to match the window size
    HandleWindowSizeUpdate();
}

void Renderer::UpdateBackgroundPosition(const Vector2& p_velocity)
{
    backgroundPosition += p_velocity;  // Update the background position based on velocity
}

void Renderer::SetBackGroundPosition(const Vector2& p_position)
{
	backgroundPosition = p_position;
}


void Renderer::DrawBackground()
{
    sf::View currentView = window->getView();
    sf::Vector2f viewCenter = currentView.getCenter();
    sf::Vector2f viewSize = currentView.getSize();

    for (auto& layer : backgroundLayers)
    {
        // Calculate the offset based on parallax factor
        float offsetX = fmod(backgroundPosition.x * layer.parallaxFactor, viewSize.x);
        float offsetY = fmod(backgroundPosition.y * layer.parallaxFactor, viewSize.y);

        // Set the texture rect to create a repeating background
        layer.sprite.setTextureRect(sf::IntRect(static_cast<int>(offsetX), static_cast<int>(offsetY), viewSize.x, viewSize.y));

        // Set the position of the background layer to match the view center
        layer.sprite.setPosition(viewCenter.x - viewSize.x / 2, viewCenter.y - viewSize.y / 2);

        window->draw(layer.sprite);
    }
}

void Renderer::HandleWindowSizeUpdate()
{
	sf::View currentView = window->getView();
	sf::Vector2f viewSize = currentView.getSize();
    for(auto& layer : backgroundLayers)
    {
        layer.sprite.setScale(viewSize.x / layer.sprite.getTexture()->getSize().x, viewSize.y / layer.sprite.getTexture()->getSize().y);
    }
}

