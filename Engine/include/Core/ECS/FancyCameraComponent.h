#pragma once
#include "RawCameraComponent.h"
class FancyCameraComponent :public RawCameraComponent
{
private:
	Vector2 targetPosition{ 0, 0 };
	Vector2 position{ 0,0 };
public:

	//Position
	/**
	 * Controls how smooth the camera moves to the newest position, the higher the value the slower the camera will move
	 */
	float positionSmoothingFactor{ 2.0f };
	bool positionSmoothing{ true };

	//Zooming
	bool zoomSmoothing{ true };
	float zoomSmoothingFactor{ 2.0f };
	float targetZoom{ 1.0f };
	float currentZoom{ 1.0f };
	float maxZoomOut{ 0.5f };
	float maxZoomIn{ 2.0f };

	bool rotationSmoothing{ true };

	FancyCameraComponent() = default;//
	FancyCameraComponent(const Vector2& p_viewSize) : RawCameraComponent(p_viewSize) {}
	~FancyCameraComponent() = default;
	void Start() override;
	void CalculateCameraSmoothing(float p_deltaTime);
	void CalculateZoomSmoothing(float p_deltaTime);
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;
	void Serialize(nlohmann::json& p_json) override;
	void Deserialize(const nlohmann::json& p_json) override;
	float GetCurrentZoom() const;
	void ZoomToFactor(const float p_zoomFactor);
	const Vector2& GetPosition() const;
};

