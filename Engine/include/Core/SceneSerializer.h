#pragma once
#include <fstream>
#include <cereal/archives/binary.hpp>
#include "cereal/types/memory.hpp"
#include "Core/Scene.h"
#include "Core/AssetManager.h"
class SceneSerializer
{
public:
	static void SaveScene(Scene& p_scene, const std::string& p_sceneFileName)
	{
		//Save scene to file using cereal binary archive
		std::ofstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
		cereal::BinaryOutputArchive oarchive(file);
		oarchive(p_scene);
		
	}

	static Scene LoadScene(const std::string& p_sceneFileName)
	{
		//Load scene from file using cereal binary archive
		std::ifstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
		cereal::BinaryInputArchive iarchive(file);
		Scene scene;
		iarchive(scene);
		return scene;
	}
};

