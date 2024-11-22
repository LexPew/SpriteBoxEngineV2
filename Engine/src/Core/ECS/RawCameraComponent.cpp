#include "Core/ECS/RawCameraComponent.h"

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

void RawCameraComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{ {"type", "RawCameraComponent"},
		{"view_size", viewSize} };
}

void RawCameraComponent::Deserialize(const nlohmann::json& p_json)
{
	p_json.at("view_size").get_to(viewSize);


	cameraView.setSize(viewSize.x, viewSize.y);

}

