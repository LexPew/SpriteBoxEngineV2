#pragma once
#include "Solid.h"
#include "SpriteComponent.h"
#include "Graphics/Renderer.h"

class SpriteSolid : public Solid
{
private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::string spriteId;
public:
	SpriteSolid() = default;
	SpriteSolid(const std::string& p_name, const Vector2& p_position, const Vector2& p_scale, const std::string& p_spriteId, const bool p_isTrigger)
	:Solid(p_name, p_position, p_scale), spriteId(p_spriteId)
	{
		SetTrigger(p_isTrigger);
	}
	~SpriteSolid();
	void Awake() override
	{
		auto sC = std::make_shared<SpriteComponent>(spriteId, AssetManager::GetInstance());
		spriteComponent = sC;
		AddComponent(sC);
		GetTransform()->onPositionChanged.Bind(&SpriteSolid::OnPositionUpdated, this);
		GetRect().SetSize(Renderer::GetInstance().GetSpriteBounds(sC->GetSprite().GetSpriteData()));
		GetRect().SetPosition(GetTransform()->GetPosition() - (GetRect().GetSize() / 2));

	}
	void Render(Renderer& p_renderer) override
	{
		Entity::Render(p_renderer);


	}
	void OnPositionUpdated(Vector2& p_position) override
	{
		GetRect().SetPosition(p_position - (GetRect().GetSize() / 2));
	}
	const std::string& GetSpriteId() { return spriteId; }
	template <class Archive>
	void save(Archive& archive) const
	{
		archive(cereal::base_class<Solid>(this), spriteId);
		DEBUG_LOG("SpriteSolid saved with spriteId: " + spriteId);
	}
	template <class Archive>
	void load(Archive& archive)
	{
		archive(cereal::base_class<Solid>(this), spriteId);
		DEBUG_LOG("SpriteSolid loaded with spriteId: " + spriteId);

	}
};

inline SpriteSolid::~SpriteSolid()
{
	RemoveComponent(spriteComponent);
	spriteComponent = nullptr;

}

CEREAL_REGISTER_TYPE(SpriteSolid)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Solid, SpriteSolid)