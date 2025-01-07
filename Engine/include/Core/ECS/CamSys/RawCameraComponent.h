#pragma once
#include <SFML/Graphics/View.hpp>

#include "Core/ECS/Component.h"
#include "Debug/DebugMacros.h"
#include "Maths/Vector2.h"

/**
 * Camera component that can be attached to an entity to allow for camera functionality,
 * extremely basic and intended for simple use or to be built upon.
 */
class RawCameraComponent : public Component
{
protected:

	Vector2 viewSize{ 1920, 1080 };

	sf::View cameraView;

public:
	RawCameraComponent() = default;
	RawCameraComponent(const Vector2& p_viewSize) : viewSize(p_viewSize)
	{
		cameraView.setSize(viewSize.x, viewSize.y);
	}

	~RawCameraComponent() = default;
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;

	const Vector2& GetViewSize() const { return viewSize; }
	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(viewSize.x, viewSize.y);
		DEBUG_LOG("RawCameraComponent saved");
	}

	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(viewSize.x, viewSize.y);
		cameraView.setSize(viewSize.x, viewSize.y);
		DEBUG_LOG("RawCameraComponent loaded");
	}
};
CEREAL_REGISTER_TYPE(RawCameraComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, RawCameraComponent)

