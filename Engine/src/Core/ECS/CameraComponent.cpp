#include "Core/ECS/CameraComponent.h"

#include "Graphics/Renderer.h"
#include "Core/ECS/Entity.h"

void CameraComponent::Start()
{
	
}

void CameraComponent::Update(float p_deltaTime)
{
	cameraView.setCenter(owner->GetTransform()->GetPosition().x, owner->GetTransform()->GetPosition().y);
}

void CameraComponent::Render(Renderer& p_renderer)
{

	p_renderer.SetView(cameraView);
}

void CameraComponent::Serialize(nlohmann::json& p_json)
{
	p_json = nlohmann::json{ {"type", "CameraComponent"},
		{"view_size", viewSize},
		{"minZoom", minZoom},
		{"maxZoom", maxZoom},
		{"current_zoom", currentZoom},
		{"current_rotation", rotation} };
}

void CameraComponent::Deserialize(const nlohmann::json& p_json)
{
	p_json.at("view_size").get_to(viewSize);
	p_json.at("minZoom").get_to(minZoom);
	p_json.at("maxZoom").get_to(maxZoom);
	p_json.at("current_zoom").get_to(currentZoom);
	p_json.at("current_rotation").get_to(rotation);

	cameraView.setSize(viewSize.x, viewSize.y);
	SetZoom(currentZoom);
	SetRotation(rotation);
}

void CameraComponent::SetZoom(const float p_zoom)
{

	if (p_zoom >= minZoom && p_zoom <= maxZoom)
	{
		cameraView.setSize(viewSize.x, viewSize.y);
		currentZoom = p_zoom;
		cameraView.zoom(currentZoom);
	}

}
