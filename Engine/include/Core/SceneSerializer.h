#pragma once
#include <fstream>

#include "Core/Scene.h"
class SceneSerializer
{
public:
	static void SaveScene(Scene& p_scene, const std::string& p_sceneFileName)
	{
		nlohmann::json sceneJson;
		//p_scene.Serialize(sceneJson);
		std::ofstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);

		file << sceneJson.dump(4);
	}

	static Scene LoadScene(const std::string& p_sceneFileName)
	{
		std::ifstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
		nlohmann::json sceneJson;
		file >> sceneJson;
		Scene loadedScene;
		//loadedScene.Deserialize(sceneJson);
		return loadedScene;
	}
};

