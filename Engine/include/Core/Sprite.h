#pragma once
#include "SpriteData.h"
#include <string>
#include "Core/AssetManager.h"
#include "Debug/DebugMacros.h"
/**
 * Sprite class, used to define the base structure of a sprite
 */
class Sprite
{
private:
    SpriteData m_data;
    int currentFrame = 0;
    float animationTimer = 0.0f;
    const AnimationData* currentAnimation = nullptr;

public:
    Sprite() = default;
    Sprite(const std::string& p_id, const AssetManager& p_assetManager)
    {
        Init(p_id, p_assetManager);
    }
    ~Sprite()
    {
		currentAnimation = nullptr;
    }
	Sprite(const Sprite& p_copy)
    {
        m_data = p_copy.GetSpriteData();
        currentAnimation = p_copy.currentAnimation;
		currentFrame = p_copy.currentFrame;
		animationTimer = p_copy.animationTimer;
    }
    Sprite& operator=(const Sprite& p_copy)
    {
		if (this == &p_copy)
		{
            return *this;
		}
		m_data = p_copy.GetSpriteData();
		currentAnimation = p_copy.currentAnimation;
		currentFrame = p_copy.currentFrame;
		animationTimer = p_copy.animationTimer;

        return *this;
    }


	void Init(const std::string& p_id, const AssetManager& p_assetManager)
	{
        //Initialize the sprite and handle if we cannot get a sprite from the asset manager
        m_data = p_assetManager.GetSprite(p_id);
		if (m_data.id == "NULL")
		{
			DEBUG_LOG_ERROR("Failed to load sprite: " + p_id);
		}
    }

    void PlayAnimation(const std::string& p_animation, const float p_deltaTime)
    {
        const auto it = m_data.animations.find(p_animation);
        if (it == m_data.animations.end())
            return;
		if (currentAnimation != &it->second)
		{
			currentFrame = it->second.startFrame;
		}
        currentAnimation = &it->second;
        animationTimer += p_deltaTime;

        if (animationTimer >= currentAnimation->frameDuration)
        {
            animationTimer = 0.0f;
            currentFrame++;
			if (currentFrame >= currentAnimation->endFrame)
			{
				currentFrame = currentAnimation->startFrame;
			}

        }
    }

	bool IsAnimationFinished() const
	{
		return currentFrame == currentAnimation->endFrame;
	}
    int GetCurrentFrame() const { return currentFrame; }
    const SpriteData& GetSpriteData() const { return m_data; }
};
