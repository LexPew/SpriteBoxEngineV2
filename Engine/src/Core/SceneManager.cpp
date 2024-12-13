#include "Core/SceneManager.h"
#include "Core/Scene.h"
#include "Core/AssetManager.h"
#include <fstream>
SceneManager SceneManager::instance;

void SceneManager::SaveScene(std::shared_ptr<Scene> p_scene, const std::string& p_sceneFileName)
{
	//Save scene to file using cereal binary archive
	std::ofstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
	cereal::BinaryOutputArchive oarchive(file);
	oarchive(p_scene);
	DEBUG_LOG("Scene saved to file: " + p_sceneFileName);
}

std::shared_ptr<Scene> SceneManager::LoadScene(const std::string& p_sceneFileName)
{
	//Load scene from file using cereal binary archive
	std::ifstream file(AssetManager::GetInstance().ResolvePath("Scenes/") + p_sceneFileName);
	cereal::BinaryInputArchive iarchive(file);
	std::shared_ptr<Scene> scene;
	iarchive(scene);
	instance.SetCurrentScene(scene);
	DEBUG_LOG("Scene loaded from file: " + p_sceneFileName);
	return scene;
}
