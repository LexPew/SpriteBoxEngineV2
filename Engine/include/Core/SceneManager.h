#pragma once
#include <cereal/archives/binary.hpp>
#include "cereal/types/memory.hpp"
#include "Core/Scene.h"

//Class: SceneManager
//Purpose: Manages the current scene and provides functionality
//			to save and load scenes using cereal
class SceneManager
{
private:
	static SceneManager* instance;

	std::shared_ptr<Scene> currentScene;

	SceneManager()
	{
		if (instance)
		{
			delete this;
			return;
		}
		instance = this;
	}
	~SceneManager()
	{
		//Cleanup
		instance = nullptr;
		currentScene = nullptr;

	}
public:
	/**
	 * @brief Save the scene to a file
	 * @param p_scene Scene to save
	 * @param p_sceneFileName Name of the file to save the scene to
	 */
	static void SaveScene(std::shared_ptr<Scene> p_scene, const std::string& p_sceneFileName);

	/**
	 * @brief Load a scene from a file
	 * @param p_sceneFileName Name of the file to load the scene from
	 * @return std::shared_ptr<Scene> The loaded scene
	 */
	static std::shared_ptr<Scene> LoadScene(const std::string& p_sceneFileName);

	/**
	 * @brief Set the current scene
	 * @param p_scene Scene to set as the current scene
	 */
	void SetCurrentScene(const std::shared_ptr<Scene>& p_scene) { currentScene = p_scene; }

	/**
	* @brief Get the current scene
	* @return std::shared_ptr<Scene> The current scene
	*/
	std::shared_ptr<Scene> GetCurrentScene() const { return currentScene; }

	static SceneManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SceneManager();
		}
		return *instance;
	}
};
