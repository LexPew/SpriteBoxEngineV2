#pragma once
#include "Core/Scene.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu() = default;
	void CreateMenu();
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
