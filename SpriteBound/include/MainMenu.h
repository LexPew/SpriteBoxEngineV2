#pragma once
#include "Core/Scene.h"

class MainMenu : public Scene
{
private:
	float parallaxRange = 5.0f;
	Vector2 parallaxOffset{ 0.0f, 0.0f };

public:
	MainMenu();
	~MainMenu() = default;
	void CreateMenu();
	void Update(const float p_deltaTime) override;

	
	template<class Archive>
	void save(Archive& archive) const
	{
		archive(cereal::base_class<Scene>(this));
	}
	template<class Archive>
	void load(Archive& archive)
	{
		archive(cereal::base_class<Scene>(this));
	}
};
CEREAL_REGISTER_TYPE(MainMenu)
CEREAL_REGISTER_POLYMORPHIC_RELATION(Scene, MainMenu)
