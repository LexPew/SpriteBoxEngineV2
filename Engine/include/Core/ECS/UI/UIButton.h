#pragma once
#include <functional>
#include <string>
#include <memory>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>

#include "Core/ECS/UI/TextData.h"
#include "UIComponent.h"
#include "Core/SoundPlayer.h"
#include "Debug/DebugMacros.h"
#include "Maths/Rect.h"
#include "Core/Sprite.h"
#include "Core/ECS/SpriteComponent.h"

//TODO: Add documentation
//TODO: Add serialization support for the on click function or some workaround for it,
//TODO: maybe a string that can be used to find the function in a map or something similar

// Class: UIButton
// Purpose: A UI component that renders a button on the screen with text, and can be clicked.
// Note: OnClick is currently not serializable so dont expect to save it, it will be lost on serialization
class UIButton : public UIComponent
{
private:
    std::function<void()> onClick;
    Rect bounds;
	TextData text;
	std::string spriteId;
    std::string soundId;

public:
    UIButton() = default;
    UIButton(const std::function<void()>& p_onClick, const TextData& p_text, const SpriteData& p_sprite, const std::string& p_onClickSoundId)
		: onClick(p_onClick), text(p_text), spriteId(p_sprite.id), soundId(p_onClickSoundId)
	{

    }
    void Init()
    {
        auto spriteComponent = std::make_shared<SpriteComponent>(spriteId, AssetManager::GetInstance());
        owner->AddComponent(spriteComponent);
		//Set bounds to the sprite bounds
		const Vector2 spriteBounds = Renderer::GetInstance().GetSpriteBounds(spriteComponent->GetSprite().GetSpriteData());
		Vector2 rectPos = (owner->GetTransform()->GetPosition() - (spriteBounds /2));
		bounds = Rect(rectPos, spriteBounds);


    }
    void Start() override
    {
		Init();

    }
    void Update(float p_deltaTime) override
    {



    }

    void HandleInput(const Vector2& p_mousePosition, const bool p_click) override
    {
        if (p_click && IsMouseOver(p_mousePosition))
        {
            if (onClick)
            {
                onClick();
                if (soundId != "") {
                    SoundPlayer::GetInstance().PlaySoundClip(soundId);
                }
                DEBUG_LOG("Clicked button");
            }
        }
    }

    void Render(Renderer& p_renderer) override
    {
		//Draw the text centered on the button
		Vector2 textPosition = owner->GetTransform()->GetPosition();
		textPosition.x -= text.text.size() * text.fontSize / 4;
		textPosition.y -= text.fontSize / 2;
		p_renderer.DrawText(text, textPosition);


    }

    template <class Archive>
    void save(Archive& archive) const
    {
        archive(cereal::base_class<UIComponent>(this), bounds, text, spriteId);
    }

    template <class Archive>
    void load(Archive& archive)
    {
		std::string spriteId;
        archive(cereal::base_class<UIComponent>(this), bounds, text, spriteId);
    }

private:
    bool IsMouseOver(const Vector2& p_mousePosition)
    {
        return bounds.Contains(p_mousePosition);
    }
};

CEREAL_REGISTER_TYPE(UIButton)
CEREAL_REGISTER_POLYMORPHIC_RELATION(UIComponent, UIButton)
