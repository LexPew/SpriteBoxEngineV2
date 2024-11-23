#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "Scene.h"

class SceneManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_currentScene;

public:
    void AddScene(const std::string& name, std::shared_ptr<Scene> scene)
    {
        m_scenes[name] = scene;
    }

    void SetCurrentScene(const std::string& name)
    {
        m_currentScene = m_scenes[name];
        m_currentScene->Start();
    }
    void Start()
    {
		if (m_currentScene)
		{
			m_currentScene->Start();
		}
    }
    void Update(float deltaTime)
    {
        if (m_currentScene)
        {
            m_currentScene->Update(deltaTime);
        }
    }

    void Render(Renderer& renderer)
    {
        if (m_currentScene)
        {
            m_currentScene->Render(renderer);
        }
    }
};
