#pragma once
#include "Core/ECS/Component.h"

class ScriptComponent : public Component
{
public:
	ScriptComponent() = default;
	~ScriptComponent() override;
	void Start() override;
	void Update(float p_deltaTime) override;
	void Render(Renderer& p_renderer) override;


	template<class Archive>
	void Save(Archive& p_archive)
	{
		p_archive(
			cereal::base_class<Component>(this));
	}
	template<class Archive>
	void Load(Archive& p_archive)
	{
		p_archive(
			cereal::base_class<Component>(this));
	}
};
CEREAL_REGISTER_TYPE(ScriptComponent)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, ScriptComponent)

