#pragma once
#include "AssetManager.h"
#include "SpriteData.h"

class Sprite
{
private:
	const SpriteData* spriteData;
	sf::Sprite sfmlSprite;
	int currentFrame;
	float animationTimer;
public:
	Sprite(const std::string& p_spriteId, const AssetManager& p_assetManager) : currentFrame(0), animationTimer(0.0f)
	{
		spriteData = &p_assetManager.GetSprite(p_spriteId);
		sfmlSprite.setTexture(spriteData->texture);
	}

    void PlayAnimation(const std::string& p_animationName, const float p_deltaTime)
    {
        if (spriteData->animations.find(p_animationName) != spriteData->animations.end())
        {
            const AnimationData& animation = spriteData->animations.at(p_animationName);
            animationTimer += p_deltaTime;

            if (animationTimer >= animation.frameDuration)
            {
                currentFrame = (currentFrame + 1) % animation.frameCount; // Loop back to the beginning frame
                animationTimer = 0.0f;
            }

            // Calculate frame dimensions
            const int frameWidth = spriteData->texture.getSize().x / spriteData->spriteSheetColumns;
            const int frameHeight = spriteData->texture.getSize().y / spriteData->spriteSheetRows;

            // Determine row and column based on the current frame
            const int totalColumns = spriteData->spriteSheetColumns;
            const int currentAnimationFrame = animation.startFrame + currentFrame;
            const int frameRow = currentAnimationFrame / totalColumns;
            const int frameColumn = currentAnimationFrame % totalColumns; // Use modulus for column calculation

            // Set the texture rectangle for the current frame
            sfmlSprite.setTextureRect(sf::IntRect(
                frameColumn * frameWidth,      // x-coordinate of the frame
                frameRow * frameHeight,       // y-coordinate of the frame
                frameWidth,                   // width of the frame
                frameHeight                   // height of the frame
            ));
        }
    }



	void Draw(sf::RenderWindow& p_window, float p_x, float p_y)
	{
		sfmlSprite.setPosition(p_x, p_y);
		p_window.draw(sfmlSprite);
	}
};
