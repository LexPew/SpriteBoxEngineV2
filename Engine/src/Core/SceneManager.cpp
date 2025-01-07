#include "Core/SceneManager.h"
#include "Core/Scene.h"
#include "Core/AssetManager.h"
#include <fstream>

#include "Debug/DebugMacros.h"
SceneManager* SceneManager::instance{nullptr};
//TODO: Update the scene manager to use the asset manager to load and save scenes
void SceneManager::SaveScene(std::shared_ptr<Scene> p_scene, const std::string& p_sceneFileName)
{
	//Save scene to file using cereal binary archive
	std::ofstream file(AssetManager::GetInstance().ResolvePath(p_sceneFileName));
	
		cereal::BinaryOutputArchive oarchive(file);
		oarchive(p_scene);
		DEBUG_LOG("Scene saved to file: " + p_sceneFileName);

	
}

std::shared_ptr<Scene> SceneManager::LoadScene(const std::string& p_sceneFileName)
{
    // Load scene from file using cereal binary archive
    std::ifstream file(AssetManager::GetInstance().ResolvePath(p_sceneFileName), std::ios::binary);

        cereal::BinaryInputArchive iarchive(file);
        std::shared_ptr<Scene> scene;
        iarchive(scene);
        DEBUG_LOG("Scene loaded from file: " + p_sceneFileName);
		return scene;
}

void SceneManager::SetCurrentScene(const std::shared_ptr<Scene>& p_scene) {
	currentScene = p_scene;
	DEBUG_LOG("Current scene set to: " + currentScene->GetSceneName());

}

std::shared_ptr<Scene> SceneManager::GetCurrentScene()
{
	
	return currentScene;
}
