#include "Graphics/Renderer.h"

void Renderer::SetView(const sf::View& p_view)
{
	window->setView(p_view);
}

void Renderer::DrawSprite(const SpriteData& p_spriteData, const int p_frameIndex,
    const Vector2& p_position, const Vector2& p_scale, bool p_flipped)
{
    sf::Sprite sprite;
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

Vector2 Renderer::GetSpriteBounds(const SpriteData& p_spriteData)
{
    float frameWidth = p_spriteData.texture.getSize().x / p_spriteData.spriteSheetColumns;
    float frameHeight = p_spriteData.texture.getSize().y / p_spriteData.spriteSheetRows;
    return Vector2{ frameWidth, frameHeight };
}
