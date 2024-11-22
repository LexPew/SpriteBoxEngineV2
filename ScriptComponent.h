#pragma once
#include "Core/ECS/Component.h"

class ScriptComponent : public Component
{
public:
	~ScriptComponent() override;
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;
	void Serialize(nlohmann::json& p_json) override;
	void Deserialize(const nlohmann::json& p_json) override;
};

