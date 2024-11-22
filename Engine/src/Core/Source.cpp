#include <SFML/Graphics.hpp>
#include "Core/AssetManager.h"
#include "Core/Entity.h"
#include "Core/Sprite.h"
#include "Core/SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/SceneSerializer.h"
#include <Utils/json.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite JSON Test");
    Renderer renderer(&window);

    AssetManager assetManager;
    assetManager.SetAssetRoot("Engine/assets");
    assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

    auto player = std::make_shared<Entity>("Player",Vector2(100, 100), Vector2(4, 4));
    player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    auto player2 = std::make_shared<Entity>("Player2",Vector2(150, 100), Vector2(4, 4));
    player2->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    auto scene = std::make_shared<Scene>();
    scene->AddEntity(player);
    scene->AddEntity(player2);
    SceneManager sceneManager;
    sceneManager.AddScene("MainScene", scene);
    sceneManager.SetCurrentScene("MainScene");

    sf::CircleShape debugDot(5.0f); // Create a small circle with radius 5
    debugDot.setFillColor(sf::Color::Red); // Set the color to red

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                // Resize the view to the size of the window
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::S)
                    player->GetTransform()->SetScale(player->GetTransform()->GetScale() + Vector2::One());
                else if (event.key.code == sf::Keyboard::L)
                {
                    scene = std::make_shared<Scene>(SceneSerializer::LoadScene("scene.json"));
                    sceneManager.AddScene("MainScene", scene);
                    sceneManager.SetCurrentScene("MainScene");
                    player = scene->FindEntityByName("Player");
                }
                else if (event.key.code == sf::Keyboard::K)
                {
                    SceneSerializer::SaveScene(*scene, "scene.json");
                }
                break;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
        }

        sceneManager.Update(deltaTime);
        sceneManager.Render(renderer);

        // Update the debug dot position
        Vector2 playerPosition = player->GetTransform()->GetPosition();
        debugDot.setPosition(playerPosition.x - debugDot.getRadius(), playerPosition.y - debugDot.getRadius());

        // Draw the debug dot
        window.draw(debugDot);

        window.display();
    }

    return 0;
}
