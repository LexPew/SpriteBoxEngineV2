#include <SFML/Graphics.hpp>
#include "Core/AssetManager.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/SceneSerializer.h"
#include <Utils/json.hpp>

#include "Core/ECS/FancyCameraComponent.h"


void RunTests()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Test");
    Renderer renderer(&window);

    AssetManager assetManager;
    assetManager.SetAssetRoot("Engine/assets");
    assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

    auto player = std::make_shared<Entity>("Player", Vector2(100, 100), Vector2(4, 4));
    player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
	Vector2 cameraSize = { 800, 600 };
    player->AddComponent(std::make_shared<FancyCameraComponent>(cameraSize));
    auto player2 = std::make_shared<Entity>("Player2", Vector2(150, 100), Vector2(4, 4));
    player2->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    
    auto scene = std::make_shared<Scene>();
    scene->AddEntity(player);
    scene->AddEntity(player2);
    SceneManager sceneManager;
    sceneManager.AddScene("MainScene", scene);
    sceneManager.SetCurrentScene("MainScene");

    sf::CircleShape debugDot(5.0f);
    debugDot.setFillColor(sf::Color::Red);

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
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::B)
                    player->GetTransform()->SetScale(player->GetTransform()->GetScale() + Vector2::One());
                else if (event.key.code == sf::Keyboard::L)
                {
                    scene = std::make_shared<Scene>(SceneSerializer::LoadScene("scene.json"));
                    sceneManager.AddScene("MainScene", scene);
                    sceneManager.SetCurrentScene("MainScene");
                    player = scene->FindEntityByName("Player");
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    SceneSerializer::SaveScene(*scene, "scene.json");
                }
                break;
            case sf::Event::MouseWheelMoved:
				player->GetComponent<FancyCameraComponent>()->ZoomToFactor
            	(player->GetComponent<FancyCameraComponent>()->GetCurrentZoom() + event.mouseWheel.delta);
				break;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(true);
            player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(false);
            player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                player->GetComponent<SpriteComponent>()->PlayAnimation("Attack");
            }
            else
            {
                player->GetComponent<SpriteComponent>()->PlayAnimation("Idle");
            }

        }

        sceneManager.Update(deltaTime);
        sceneManager.Render(renderer);

        Vector2 playerPosition = player->GetTransform()->GetPosition();
        debugDot.setPosition(playerPosition.x - debugDot.getRadius(), playerPosition.y - debugDot.getRadius());

        window.draw(debugDot);

        window.display();
    }
}
