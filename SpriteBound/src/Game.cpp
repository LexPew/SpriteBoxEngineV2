// File: SpriteBound/src/Game.cpp
#include "Game.h"

#include <SFML/Window/Event.hpp>

#include "Core/AssetManager.h"
#include "Core/SceneManager.h"
#include "Core/ECS/SpriteComponent.h"
#include "Core/ECS/UI/UIButton.h"
#include "Core/ECS/UI/UILabel.h"
#include "Debug/DebugMacros.h"
#include "MainMenu.h" // Include the MainMenu header

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

void Game::Update()
{
    deltaTime = clock.restart().asSeconds();
    SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);
    // Update game logic
}

void Game::Render()
{
    gameWindow.clear();
    SceneManager::GetInstance().GetCurrentScene()->Render(Renderer::GetInstance());
    gameWindow.display();
}
