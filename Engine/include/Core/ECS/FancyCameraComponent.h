#pragma once
#include "RawCameraComponent.h"
/**
 * Camera component based upon the RawCameraComponent,
 * adds additional functionality such as camera smoothing,
 * zooming, rotation and camera shake
 */
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

	//Rotation
	bool rotationSmoothing{ true };

	//Camera shake
	Vector2 shakeOffset{ 0,0 };
	float shakeMagnitude{ 0 };
	float shakeFrequency{ 0 };
	float shakeDuration{ 0 };
	float shakeElapsedTime{ 0 };
	bool isShaking{ false };

	FancyCameraComponent() = default;

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

	void ApplyCameraShake(float p_deltaTime);

	void AddCameraShake(float p_amplitude, float p_frequency, float p_time);
};

