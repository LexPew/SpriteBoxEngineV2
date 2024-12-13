#include "Core/SceneSerializer.h"

SceneSerializer SceneSerializer::instance;

void SceneSerializer::SaveScene(std::shared_ptr<Scene> p_scene, const std::string& p_sceneFileName)
{
	//Save scene to file using cereal binary archive
	std::ofstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
	cereal::BinaryOutputArchive oarchive(file);
	oarchive(p_scene);
}

std::shared_ptr<Scene> SceneSerializer::LoadScene(const std::string& p_sceneFileName)
{
	//Load scene from file using cereal binary archive
	std::ifstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
	cereal::BinaryInputArchive iarchive(file);
	std::shared_ptr<Scene> scene;
	iarchive(scene);
	instance.SetCurrentScene(scene);
	return scene;
}
