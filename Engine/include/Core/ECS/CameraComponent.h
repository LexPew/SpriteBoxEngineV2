#pragma once
#include <SFML/Graphics/View.hpp>

#include "Component.h"
#include "Maths/Vector2.h"

class CameraComponent : public Component
{
private:

	Vector2 viewSize{ 1920, 1080 };

	sf::View cameraView;
	float minZoom{ 0.1f };
	float maxZoom{ 10.0f };
	float currentZoom{ 1.0f };
	float rotation{ 0.0f };
public:
	CameraComponent(const Vector2& p_viewSize) : viewSize(p_viewSize)
	{
		cameraView.setSize(viewSize.x, viewSize.y);
	}

	~CameraComponent() = default;
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;
	void Serialize(nlohmann::json& p_json) override;
	void Deserialize(const nlohmann::json& p_json) override;

	float GetZoom() const { return currentZoom; }
	void SetZoom(const float p_zoom);

	float GetRotation() const { return rotation; }
	void SetRotation(const float p_rotation) { rotation = p_rotation; cameraView.setRotation(p_rotation); }
};

