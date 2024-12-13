#pragma once
#include <fstream>
#include <cereal/archives/binary.hpp>
#include "cereal/types/memory.hpp"
#include "Core/Scene.h"
#include "Core/AssetManager.h"
class SceneSerializer
{
public:
	static SceneSerializer instance;

	std::shared_ptr<Scene> currentScene;

	static void SaveScene(std::shared_ptr<Scene> p_scene, const std::string& p_sceneFileName);
	static std::shared_ptr<Scene> LoadScene(const std::string& p_sceneFileName);
	void SetCurrentScene(std::shared_ptr<Scene> p_scene) { currentScene = p_scene; }
};

