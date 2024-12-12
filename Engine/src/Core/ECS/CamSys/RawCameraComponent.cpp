#include "Core/ECS/CamSys/RawCameraComponent.h"

#include "Graphics/Renderer.h"
#include "Core/ECS/Entity.h"

void RawCameraComponent::Start()
{
	
}

void RawCameraComponent::Update(float p_deltaTime)
{
	cameraView.setCenter(owner->GetTransform()->GetPosition().x, owner->GetTransform()->GetPosition().y);
}

void RawCameraComponent::Render(Renderer& p_renderer)
{

	p_renderer.SetView(cameraView);
}


