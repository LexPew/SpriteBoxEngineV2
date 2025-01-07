#pragma once
#include "RawCameraComponent.h"
#include "Debug/DebugMacros.h"
class TransformComponent;
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
	float rotationSmoothingFactor{ 2.0f };
	float targetRotation{ 0.0f };
	float currentRotation{ 0.0f };
	float maxAngle{ 90.0f };

	//Camera shake
	Vector2 shakeOffset{ 0,0 };
	float shakeMagnitude{ 0 };
	float shakeFrequency{ 0 };
	float shakeDuration{ 0 };
	float shakeElapsedTime{ 0 };
	bool isShaking{ false };
	
	//Bobbing

	FancyCameraComponent() = default;

	FancyCameraComponent(const Vector2& p_viewSize) : RawCameraComponent(p_viewSize) {}

	~FancyCameraComponent() = default;

	void CalculateCameraSmoothing(float p_deltaTime);

	void CalculateZoomSmoothing(float p_deltaTime);

	void CalculateCameraRotation(float p_deltaTime);

	void Update(float p_deltaTime) override;

	void Render(Renderer& p_renderer) override;

	float GetCurrentZoom() const;
	float GetCurrentRotation() const;


	void ZoomToFactor(const float p_zoomFactor);
	void RotateTo(const float p_angle);

	void ApplyCameraShake(float p_deltaTime);

	void AddCameraShake(float p_amplitude, float p_frequency, float p_time);


	template<class Archive>
	void save(Archive& p_archive) const
	{
		p_archive(cereal::base_class<RawCameraComponent>(this),

			targetPosition,
			position,
			positionSmoothingFactor,
			positionSmoothing,
			zoomSmoothing,
			zoomSmoothingFactor,
			targetZoom,
			currentZoom,
			maxZoomOut,
			maxZoomIn,
			rotationSmoothing,
			rotationSmoothingFactor,
			targetRotation,
			currentRotation,
			maxAngle,
			shakeOffset,
			shakeMagnitude,
			shakeFrequency,
			shakeDuration,
			shakeElapsedTime,
			isShaking);
		DEBUG_LOG("FancyCameraComponent saved");
	}

	template<class Archive>
	void load(Archive& p_archive)
	{
		p_archive(cereal::base_class<RawCameraComponent>(this),
			targetPosition,
			position,
			positionSmoothingFactor,
			positionSmoothing,
			zoomSmoothing,
			zoomSmoothingFactor,
			targetZoom,
			currentZoom,
			maxZoomOut,
			maxZoomIn,
			rotationSmoothing,
			rotationSmoothingFactor,
			targetRotation,
			currentRotation,
			maxAngle,
			shakeOffset,
			shakeMagnitude,
			shakeFrequency,
			shakeDuration,
			shakeElapsedTime,
			isShaking);
		DEBUG_LOG("FancyCameraComponent loaded");
	}
};
CEREAL_REGISTER_TYPE(FancyCameraComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(RawCameraComponent, FancyCameraComponent)

