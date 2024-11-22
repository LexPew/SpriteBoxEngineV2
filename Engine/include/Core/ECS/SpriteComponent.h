#pragma once
#include "Core/ECS/Component.h"
#include "Core/Sprite.h"
#include "Core/AssetManager.h"

class SpriteComponent : public Component
{
private:
    Sprite sprite;
    bool flipped{ false };
	std::string currentAnimation{ "Idle" };
public:
    SpriteComponent(const std::string& p_id, const AssetManager& p_assetManager)
        : sprite(p_id, p_assetManager) {}

    void Start() override;

    void Update(float p_deltaTime) override;

    void Render(Renderer& p_renderer) override;

	void PlayAnimation(const std::string& p_animation) { currentAnimation = p_animation; }
	void Flip() { flipped = !flipped; }
	void Flip(bool p_flip) { flipped = p_flip; }

    void Serialize(nlohmann::json& p_json) override;

    void Deserialize(const nlohmann::json& p_json) override;
};
