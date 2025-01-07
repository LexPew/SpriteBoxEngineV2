#include "Core/ECS/UI/UILabel.h"
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"

void UILabel::OnPositionUpdated(Vector2& p_newPosition)
{
	//Center the text on the owner's position
	std::cout << "Text bounds: " << Renderer::GetInstance().GetTextSize(textData) << std::endl;
	textPosition = (p_newPosition - (Renderer::GetInstance().GetTextSize(textData) / 2));
	std::cout << "Position Updated " << textPosition << std::endl;
}

void UILabel::Awake()
{
	UIComponent::Awake();
	owner->GetTransform()->onPositionChanged.Bind(&UILabel::OnPositionUpdated, this);

 }

void UILabel::Render(Renderer& p_renderer)
{
	//Draw the text at the specified position
	p_renderer.DrawText(textData, textPosition);
}
