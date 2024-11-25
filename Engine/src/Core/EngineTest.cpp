#include <SFML/Graphics.hpp>
#include "Core/AssetManager.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/SpriteComponent.h"
#include "Graphics/Renderer.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/SceneSerializer.h"
#include <Utils/json.hpp>
#include "Core/ECS/CamSys/FancyCameraComponent.h"
#include "Core/ECS/RigidBodyComponent.h"
#include "Physics/Impulse2DLite.h"
void RunTests()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Test");
    Renderer renderer(&window);

    AssetManager assetManager;
    assetManager.SetAssetRoot("Engine/assets");
    assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

    auto player = std::make_shared<Entity>("Player", Vector2(100, 100), Vector2(4, 4));
    player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
	player->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0, 0, 64, 64)));

    Vector2 cameraSize = { 800, 600 };
    player->AddComponent(std::make_shared<FancyCameraComponent>(cameraSize));

    auto player2 = std::make_shared<Entity>("Player", Vector2(100, 250), Vector2(4, 4));
    player2->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    player2->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0, 0, 64, 64)));


	auto floor = std::make_shared<Entity>("Floor", Vector2(0, 400), Vector2(1, 1));
	floor->AddComponent(std::make_shared<RigidBodyComponent>(0.0f, 0.2f, Rect(0, 0, 64, 500)));
    auto scene = std::make_shared<Scene>();
    scene->AddEntity(player);
    scene->AddEntity(player2);
	scene->AddEntity(floor);
    

    Physics physicsEngine;

    SceneManager sceneManager;
    sceneManager.AddScene("MainScene", scene);
    sceneManager.SetCurrentScene("MainScene");

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
                else if (event.key.code == sf::Keyboard::P)
                {
                    // Add functionality for 'P' key if needed
                }
                break;
            case sf::Event::MouseWheelMoved:
                player->GetComponent<FancyCameraComponent>()->ZoomToFactor(
                    player->GetComponent<FancyCameraComponent>()->GetCurrentZoom() + event.mouseWheel.delta * 5.0f);
                break;
            }
        }

        float deltaTime = clock.restart().asSeconds();
		physicsEngine.Update(deltaTime);
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player2->GetComponent<RigidBodyComponent>()->GetBody().ApplyForce({ 0,-100 });
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			player->GetComponent<FancyCameraComponent>()
                ->RotateTo(player->GetComponent<FancyCameraComponent>()->GetCurrentRotation() - 10);
        }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			player->GetComponent<FancyCameraComponent>()
				->RotateTo(player->GetComponent<FancyCameraComponent>()->GetCurrentRotation() + 10);
		}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            player->GetComponent<FancyCameraComponent>()->RotateTo(0);
        }

        Body& rigidbody = player->GetComponent<RigidBodyComponent>()->GetBody();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(true);
            rigidbody.SetVelocity({ -100, rigidbody.GetVelocity().y });
            //player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(false);
            rigidbody.SetVelocity({ 100, rigidbody.GetVelocity().y });
           // player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
        }
        else
        {
            rigidbody.SetVelocity({ 0, rigidbody.GetVelocity().y });
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                player->GetComponent<SpriteComponent>()->PlayAnimation("Attack");
                player->GetComponent<FancyCameraComponent>()->AddCameraShake(4, 4, 0.1f);
            }
            else
            {
                player->GetComponent<SpriteComponent>()->PlayAnimation("Idle");
            }
        }
		

        sceneManager.Update(deltaTime);
        sceneManager.Render(renderer);

        // Debug render for rigid bodies
        for (const auto& entity : scene->GetEntities())
        {
            if (auto rigidBody = entity->GetComponent<RigidBodyComponent>())
            {
                rigidBody->DebugRender(window);
            }
        }

        window.display();
    }
}
