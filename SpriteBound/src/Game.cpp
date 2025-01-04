#include "Game.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Window/Event.hpp>

#include "Core/AssetManager.h"
#include "Core/SceneManager.h"
#include "Core/ECS/SpriteComponent.h"

#include "Debug/DebugMacros.h"

#include "MainMenu.h" 
#include "Debug/PerformanceMetrics.h"

bool Game::Initialize()
{
    DEBUG_LOG("Creating game window");
    gameWindow.create(sf::VideoMode().getDesktopMode(), "SpriteBound");
    if (!gameWindow.isOpen())
    {
        DEBUG_LOG("Game window failed to create, initialization unsuccessful");
        return false;
    }
    DEBUG_LOG("Game window created successfully");
    Renderer::GetInstance().SetWindow(&gameWindow);

    AssetManager::GetInstance().SetAssetRoot("Spritebound/assets");
	ImGui::SFML::Init(gameWindow);
    // Load the MainMenu scene by default
    auto mainMenuScene = std::make_shared<MainMenu>();
    SceneManager::GetInstance().SetCurrentScene(mainMenuScene);

    isRunning = true;
    Loop();
}

void Game::Loop()
{
    while (isRunning)
    {
        HandleEvents();
        Update();
        Render();
    }
    Cleanup();
}

void Game::Cleanup()
{
    // Cleanup any resources and free memory
    AssetManager::Cleanup();
}

void Game::HandleEvents()
{
    sf::Event event;
    while (gameWindow.pollEvent(event))
    {
		ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            gameWindow.close();
            isRunning = false;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // SceneManager::SaveScene(SceneManager::GetInstance().GetCurrentScene(), "MainGame");
            SceneManager::GetInstance().GetCurrentScene()->HandleInput
            (Vector2(event.mouseButton.x, event.mouseButton.y), true);
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {

            SceneManager::GetInstance().GetCurrentScene()->HandleInput
            (Vector2(event.mouseMove.x, event.mouseMove.y), false);
        }
    }
}

void Game::UpdatePerformanceMetrics()
{
#ifdef _DEBUG
	PerformanceMetrics::GetInstance()->Update(deltaTime);
	ImGui::Begin("Performance Metrics");
	ImGui::Text("FPS: %.2f", PerformanceMetrics::GetInstance()->GetFrameRate());
	ImGui::Text("Averaged FPS: %.2f", PerformanceMetrics::GetInstance()->GetAveragedFrameRate());
	ImGui::End();
#endif

}

void Game::Update()
{
    deltaTime = clock.restart().asSeconds();
    SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);
	ImGui::SFML::Update(gameWindow, sf::seconds(deltaTime));
    UpdatePerformanceMetrics();
	// Update game logic
}

void Game::Render()
{
    gameWindow.clear();
    SceneManager::GetInstance().GetCurrentScene()->Render(Renderer::GetInstance());
	ImGui::SFML::Render(gameWindow);
    gameWindow.display();
}
