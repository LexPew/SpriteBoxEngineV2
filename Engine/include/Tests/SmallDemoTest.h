#pragma once
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"

#include "PlayerActor.h"
#include "Core/ECS/SpriteSolid.h"
#include "Graphics/Renderer.h"
#include "SFML/Graphics.hpp"

#include <imgui.h>

#include "imgui-SFML.h"

class SmallDemoTest
{
public:
	SmallDemoTest() = default;
	~SmallDemoTest() = default;

	bool isRunning{ true };

    void SmallGameTest()
    {
        //---> SCENE EDITOR <---//

        // Create the renderer and window
        sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Small Game Test");
        Renderer::GetInstance().SetWindow(&window);

        //CREATE SCENE

        // Create the asset manager
        AssetManager::GetInstance().SetAssetRoot("SpriteBound/assets");
        AssetManager::GetInstance().LoadSprite("sprites/Adventurer.json");
        AssetManager::GetInstance().LoadSprite("sprites/Grass_Platform.json");
        AssetManager::GetInstance().LoadSprite("sprites/Grass_PlatformShort.json");

        // Load and add parallax background layers
        for (int i = 1; i < 6; i++)
        {
            std::string textureId = "PB" + std::to_string(i);
            std::string texturePath = "sprites/parallaxbackground/" + std::to_string(i) + ".png";
            AssetManager::GetInstance().LoadTexture(textureId, texturePath);
            Renderer::GetInstance().AddBackgroundLayer(textureId, static_cast<float>(i));
        }

        // Create the scene
        std::shared_ptr<Scene> smallGameTestScene = std::make_shared<Scene>();

        auto player = std::make_shared<PlayerActor>("Player", Vector2::Zero(), Vector2::One(), "Adventurer");

        // Set the origin offset
        std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed for randomness

        // Ensure the first platform is below the player
        Vector2 firstPlatformPosition(0, 100); // Position the first platform below the player
        Vector2 firstPlatformScale(1.0f, 1.0f);
        auto firstPlatform = std::make_shared<SpriteSolid>("Floor", firstPlatformPosition, firstPlatformScale, "Grass_Platform", false);
        smallGameTestScene->AddEntity(firstPlatform);

        // Generate the rest of the platforms with random positions and scales
        int numberOfPlatforms = 10;
        for (int i = 1; i < numberOfPlatforms; i++)
        {
            float xPos = 200 * i + (std::rand() % 100 - 50); // Randomize x position slightly
            float yPos = 50 + (std::rand() % 100 - 50); // Randomize y position slightly
            Vector2 position(xPos, yPos);
            Vector2 scale(1.0f + static_cast<float>(std::rand() % 50) / 100.0f, 1.0f); // Randomize scale slightly

            // Randomly choose between the two platform types
            std::string platformType = (std::rand() % 2 == 0) ? "Grass_Platform" : "Grass_PlatformShort";
            auto platform = std::make_shared<SpriteSolid>("Floor", position, scale, platformType, false);
            smallGameTestScene->AddEntity(platform);
            // If we are creating the last platform then add another solid as a trigger on top of it
            if (i == numberOfPlatforms - 1)
            {
                Vector2 triggerPosition = position;
                triggerPosition.y -= 50;
                auto trigger = std::make_shared<SpriteSolid>("Trigger", triggerPosition, Vector2(1.0f, 1.0f), "Grass_Platform", true);
                // Set the function for trigger on enter to load the scene MainGame.scene
				trigger->onTriggerEnter += Sharp::EventHandler::Bind(&SmallDemoTest::SmallGameTest_OnTriggerEnter, this);
                smallGameTestScene->AddEntity(trigger);
            }

        }

        // Add the entities to the scene
        smallGameTestScene->AddEntity(player);
        SceneManager::SaveScene(smallGameTestScene, "scenes/Level1.scene");
        SceneManager::GetInstance().SetCurrentScene(smallGameTestScene);


        //GAME

        // Delta time clock
        sf::Clock deltaClock;

        //---> Game Loop <---//
        SceneManager::GetInstance().GetCurrentScene()->Awake();
        SceneManager::GetInstance().GetCurrentScene()->Start();
        window.setFramerateLimit(144);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    InputManager::GetInstance().UpdateScrollWheelDelta(event.mouseWheelScroll.delta);
                }
            }

            float deltaTime = deltaClock.restart().asSeconds();

            // Update scene and render
            InputManager::GetInstance().Update();
            SceneManager::GetInstance().GetCurrentScene()->Update(deltaTime);

            window.clear();

            // Render background and scene
            Renderer::GetInstance().DrawBackground();
            SceneManager::GetInstance().GetCurrentScene()->Render(Renderer::GetInstance());

            window.display();
        }

        // After the game loop, shutdown ImGui-SFML
        ImGui::SFML::Shutdown();
		isRunning = false;
    }

    void SmallGameTest_OnTriggerEnter(Actor& p_actor)
    {
        auto scene = SceneManager::LoadScene("scenes/Level1.scene");
		SceneManager::GetInstance().SetCurrentScene(scene);
    }
};




