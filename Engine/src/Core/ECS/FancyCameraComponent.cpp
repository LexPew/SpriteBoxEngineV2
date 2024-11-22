#include "Core/ECS/FancyCameraComponent.h"

#include "Core/ECS/Entity.h"
#include <random>

void FancyCameraComponent::Start()
{
	//RawCameraComponent::Start();

}

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
}

void FancyCameraComponent::Render(Renderer& p_renderer)
{
	RawCameraComponent::Render(p_renderer);
}

void FancyCameraComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{
		{"type", "FancyCameraComponent"},
		{"view_size", viewSize}, 
		{"positionSmoothingFactor", positionSmoothingFactor},
		{"positionSmoothing", positionSmoothing},
		{"zoomSmoothing", zoomSmoothing},
		{"zoomSmoothingFactor", zoomSmoothingFactor},
		{"targetZoom", targetZoom},
		{"currentZoom", currentZoom}, 
		{"maxZoomOut", maxZoomOut},
		{"maxZoomIn", maxZoomIn},
		{"rotationSmoothing", rotationSmoothing},
		{"rotationSmoothingFactor", rotationSmoothingFactor},
		{"targetRotation", targetRotation},
		{"currentRotation", currentRotation},
		{"maxAngle", maxAngle },
		{"shakeOffset", shakeOffset},
		{"shakeMagnitude", shakeMagnitude},
		{"shakeFrequency", shakeFrequency},
		{"shakeDuration", shakeDuration},
		{"shakeElapsedTime", shakeElapsedTime},
		{"isShaking", isShaking}
		 };
}

void FancyCameraComponent::Deserialize(const nlohmann::json& p_json)
{
	p_json.at("view_size").get_to(viewSize);
	p_json.at("positionSmoothingFactor").get_to(positionSmoothingFactor);
	p_json.at("positionSmoothing").get_to(positionSmoothing);
	p_json.at("zoomSmoothing").get_to(zoomSmoothing);
	p_json.at("zoomSmoothingFactor").get_to(zoomSmoothingFactor);
	p_json.at("targetZoom").get_to(targetZoom);
	p_json.at("currentZoom").get_to(currentZoom);
	p_json.at("maxZoomOut").get_to(maxZoomOut);
	p_json.at("maxZoomIn").get_to(maxZoomIn);
	p_json.at("rotationSmoothing").get_to(rotationSmoothing);
	p_json.at("rotationSmoothingFactor").get_to(rotationSmoothingFactor);
	p_json.at("targetRotation").get_to(targetRotation);
	p_json.at("currentRotation").get_to(currentRotation);
	p_json.at("maxAngle").get_to(maxAngle);
	p_json.at("shakeOffset").get_to(shakeOffset);
	p_json.at("shakeMagnitude").get_to(shakeMagnitude);
	p_json.at("shakeFrequency").get_to(shakeFrequency);
	p_json.at("shakeDuration").get_to(shakeDuration);
	p_json.at("shakeElapsedTime").get_to(shakeElapsedTime);
	p_json.at("isShaking").get_to(isShaking);



	cameraView.setSize(viewSize.x, viewSize.y);
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


