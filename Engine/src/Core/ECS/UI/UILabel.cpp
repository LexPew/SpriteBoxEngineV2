#include "Core/ECS/UI/UILabel.h"
#include "Core/ECS/Entity.h"
#include "Graphics/Renderer.h"

void UILabel::Render(Renderer& p_renderer)
{
	p_renderer.DrawText(textData, owner->GetTransform()->GetPosition());
}
