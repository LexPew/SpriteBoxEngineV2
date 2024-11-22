#include "Core/SpriteComponent.h"
#include "Core/Entity.h"
#include "Graphics/Renderer.h"
#include "Core/TransformComponent.h"

void SpriteComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{ {"type", "SpriteComponent"}, {"sprite_id",sprite.GetSpriteData().id} };
}

void SpriteComponent::Deserialize(const nlohmann::json& p_json)
{
	std::string sprite_id;
	p_json.at("sprite_id").get_to(sprite_id);
	sprite = Sprite(sprite_id, AssetManager::GetInstance());
}

void SpriteComponent::Start()
{
	//Do start stuff
}

void SpriteComponent::Update(float p_deltaTime)
{
	sprite.PlayAnimation("Idle", p_deltaTime);
}

void SpriteComponent::Render(Renderer& p_renderer)
{
	auto transform = owner->GetTransform();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	p_renderer.DrawSprite(sprite.GetSpriteData(), sprite.GetCurrentFrame(), position, scale);
}
