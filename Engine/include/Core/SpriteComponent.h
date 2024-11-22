#pragma once
#include "Core/Component.h"
#include "Sprite.h"
#include "Core/AssetManager.h"

class SpriteComponent : public Component
{
private:
    Sprite sprite;

public:
    SpriteComponent(const std::string& p_id, const AssetManager& p_assetManager)
        : sprite(p_id, p_assetManager) {}

    void Serialize(nlohmann::json& p_json) override;
    void Deserialize(const nlohmann::json& p_json) override;


    void Start() override;

    void Update(float p_deltaTime) override;

    void Render(Renderer& p_renderer) override;
};
