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
    int m_currentFrame = 0;
    float m_animationTimer = 0.0f;
    const AnimationData* m_currentAnimation = nullptr;

public:
    Sprite() = default;
    Sprite(const std::string& p_id, const AssetManager& p_assetManager)
    {
        Init(p_id, p_assetManager);
    }
    ~Sprite()
    {
		delete m_currentAnimation;
		m_currentAnimation = nullptr;
    }
	Sprite(const Sprite& p_copy)
    {
        m_data = p_copy.GetSpriteData();
        m_currentAnimation = p_copy.m_currentAnimation;
		m_currentFrame = p_copy.m_currentFrame;
		m_animationTimer = p_copy.m_animationTimer;
    }
    Sprite& operator=(const Sprite& p_copy)
    {
		if (this == &p_copy)
		{
            return *this;
		}
		m_data = p_copy.GetSpriteData();
		m_currentAnimation = p_copy.m_currentAnimation;
		m_currentFrame = p_copy.m_currentFrame;
		m_animationTimer = p_copy.m_animationTimer;

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
		if (m_currentAnimation != &it->second)
		{
			m_currentFrame = it->second.startFrame;
		}
        m_currentAnimation = &it->second;
        m_animationTimer += p_deltaTime;

        if (m_animationTimer >= m_currentAnimation->frameDuration)
        {
            m_animationTimer = 0.0f;
            m_currentFrame++;
			if (m_currentFrame >= m_currentAnimation->endFrame)
			{
				m_currentFrame = m_currentAnimation->startFrame;
			}

        }
    }

	bool IsAnimationFinished() const
	{
		return m_currentFrame == m_currentAnimation->endFrame;
	}
    int GetCurrentFrame() const { return m_currentFrame; }
    const SpriteData& GetSpriteData() const { return m_data; }
};
