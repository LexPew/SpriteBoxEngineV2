#pragma once
#include <SFML/Graphics/View.hpp>

#include "Component.h"
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
	void Serialize(nlohmann::json& p_json) override;
	void Deserialize(const nlohmann::json& p_json) override;

};

