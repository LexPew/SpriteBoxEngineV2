#include "Core/ECS/SpriteComponent.h"
#include "Core/Sprite.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/TransformComponent.h"
#include "Graphics/Renderer.h"




void SpriteComponent::Start()
{
	//Do start stuff
}

void SpriteComponent::Update(float p_deltaTime)
{
	sprite.PlayAnimation(currentAnimation, p_deltaTime);
}

void SpriteComponent::Render(Renderer& p_renderer)
{
	auto transform = owner->GetTransform();
	Vector2 position = transform->GetPosition();
	Vector2 scale = transform->GetScale();
	p_renderer.DrawSprite(sprite.GetSpriteData(), sprite.GetCurrentFrame(), position, scale, flipped);
}

void SpriteComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{ {"type", "SpriteComponent"}, {"sprite_id",sprite.GetSpriteData().id},
	{"flipped", flipped}, {"currentAnimation", currentAnimation} };
}

void SpriteComponent::Deserialize(const nlohmann::json& p_json)
{
	std::string sprite_id;
	p_json.at("sprite_id").get_to(sprite_id);
	p_json.at("flipped").get_to(flipped);
	p_json.at("currentAnimation").get_to(currentAnimation);
	sprite = Sprite(sprite_id, AssetManager::GetInstance());

}
