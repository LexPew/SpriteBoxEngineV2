#include "Core/ECS/CamSys/FancyCameraComponent.h"

#include "Core/ECS/Entity.h"
#include <random>


void FancyCameraComponent::CalculateCameraSmoothing(float p_deltaTime)
{
	targetPosition = owner->GetTransform()->GetPosition();

	if (positionSmoothing)
	{
		Vector2 diff = targetPosition - position;
		position += diff * p_deltaTime * positionSmoothingFactor;
	}
	else
	{
		position = targetPosition;
	}
	cameraView.setCenter(position.x, position.y);
}

void FancyCameraComponent::CalculateZoomSmoothing(float p_deltaTime)
{
	if (zoomSmoothing)
	{
		float diff = targetZoom - currentZoom;
		currentZoom += diff * p_deltaTime * zoomSmoothingFactor;
		cameraView.setSize(viewSize.x / currentZoom, viewSize.y / currentZoom);
	}

}

void FancyCameraComponent::CalculateCameraRotation(float p_deltaTime)
{
	if (rotationSmoothing)
	{
		float diff = targetRotation - currentRotation;
		currentRotation += diff * p_deltaTime * rotationSmoothingFactor;
		cameraView.setRotation(currentRotation);
	}
}

void FancyCameraComponent::Update(float p_deltaTime)
{
	CalculateCameraSmoothing(p_deltaTime);
	CalculateCameraRotation(p_deltaTime);
	CalculateZoomSmoothing(p_deltaTime);
	ApplyCameraShake(p_deltaTime);

	// Update the view with the camera's settings
	sf::View view;
	view.setCenter(position.x + shakeOffset.x, position.y + shakeOffset.y);
	view.setSize(viewSize.x / currentZoom, viewSize.y / currentZoom);
	view.setRotation(currentRotation);
}

void FancyCameraComponent::Render(Renderer& p_renderer)
{
	RawCameraComponent::Render(p_renderer);
}


float FancyCameraComponent::GetCurrentZoom() const
{
	return currentZoom;
}

float FancyCameraComponent::GetCurrentRotation() const
{
	return currentRotation;
}

void FancyCameraComponent::ZoomToFactor(const float p_zoomFactor)
{
	targetZoom = std::clamp(p_zoomFactor, maxZoomOut, maxZoomIn);

	if(!zoomSmoothing)
	{
		cameraView.setSize(viewSize.x / targetZoom, viewSize.y / targetZoom);
	}

}
void FancyCameraComponent::RotateTo(const float p_angle)
{
	float angleClamped = std::clamp(p_angle, -maxAngle, maxAngle);
	if (!rotationSmoothing)
	{
		cameraView.setRotation(angleClamped);
	}
	else 
	{
		targetRotation = angleClamped;

	}


}
void FancyCameraComponent::ApplyCameraShake(float p_deltaTime)
{
	if (!isShaking) return;

	shakeElapsedTime += p_deltaTime;
	if (shakeElapsedTime >= shakeDuration)
	{
		isShaking = false;
		shakeOffset = Vector2::Zero();
		return;
	}

	// Initialize random number generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-1.0, 1.0);

	// Calculate the shake offset
	float shakeX = dis(gen) * shakeMagnitude;
	float shakeY = dis(gen) * shakeMagnitude;
	shakeOffset = Vector2(shakeX, shakeY);

	// Apply the shake to the camera position
	Vector2 shakenPosition = position + shakeOffset;
	cameraView.setCenter(shakenPosition.x, shakenPosition.y);
}

void FancyCameraComponent::AddCameraShake(float p_magnitude, float p_frequency, float p_time)
{
	shakeMagnitude	 = p_magnitude;
	shakeFrequency = p_frequency;
	shakeDuration = p_time;
	shakeElapsedTime = 0.0f;
	isShaking = true;
}


