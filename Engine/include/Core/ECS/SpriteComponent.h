#pragma once
#include "Core/ECS/Component.h"
#include "Core/Sprite.h"
#include "Core/AssetManager.h"
#include "Maths/Vector2.h"


class SpriteComponent : public Component
{
public:
    Sprite sprite;
    bool flipped{ false };
	std::string currentAnimation{ "Idle" };

public:
	SpriteComponent() = default;
    SpriteComponent(const std::string& p_id, const AssetManager& p_assetManager)
        : sprite(p_id, p_assetManager) {}

    void Start() override;

    void Update(float p_deltaTime) override;

    void Render(Renderer& p_renderer) override;

	void PlayAnimation(const std::string& p_animation) { currentAnimation = p_animation; }
	void Flip() { flipped = !flipped; }
	void Flip(const bool p_flip) { flipped = p_flip; }

	
	void SetSprite(const std::string& p_id, const AssetManager& p_assetManager)
	{
		sprite.Init(p_id, p_assetManager);
	}

	Sprite& GetSprite() { return sprite; }

	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(sprite.GetSpriteData().id, flipped, currentAnimation);
	}

	template<class Archive>
	void load(Archive& p_archive)
	{
		std::string sprite_id;
		p_archive(cereal::base_class<Component>(this), sprite_id, flipped, currentAnimation);
		sprite = Sprite(sprite_id, AssetManager::GetInstance());
	}
};
CEREAL_REGISTER_TYPE(SpriteComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component,SpriteComponent)


