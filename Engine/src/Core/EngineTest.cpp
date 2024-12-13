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
#include <cereal/archives/json.hpp>

void RunTests()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine Test");

    Renderer renderer(&window);
    AssetManager assetManager;
    Physics physicsEngine;
    SceneManager sceneManager;


    assetManager.SetAssetRoot("Engine/assets");
    assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

    auto player = std::make_shared<Entity>("Player", Vector2(100, 100), Vector2(2, 2));
    player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    const Vector2 spriteBounds = renderer.GetSpriteBounds(assetManager.GetSprite("Adventurer"));
	player->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0,0,spriteBounds.y, spriteBounds.y)));

    Vector2 cameraSize = { 800, 600 };
    player->AddComponent(std::make_shared<FancyCameraComponent>(cameraSize));

    auto player2 = std::make_shared<Entity>("Player", Vector2(100, 250), Vector2(2, 2));
    player2->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
    player2->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0, 0, spriteBounds.y, spriteBounds.y)));


	auto floor = std::make_shared<Entity>("Floor", Vector2(0, 400), Vector2(1, 1));
	floor->AddComponent(std::make_shared<RigidBodyComponent>(0.0f, 0.2f, Rect(0, 0, 64, 500)));

	auto testEntity = std::make_shared<Entity>("TestEntity");
	testEntity->GetTransform()->SetPosition(Vector2(200, 200));



    auto scene = std::make_shared<Scene>();
    scene->AddEntity(player);
    scene->AddEntity(player2);
	scene->AddEntity(floor);
	scene->AddEntity(testEntity);

    sceneManager.AddScene("MainScene", scene);
    sceneManager.SetCurrentScene("MainScene");

    physicsEngine.SetGravity({ 0,80 });
    physicsEngine.SetGroundedGravity({ 0,1 });






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
                    // = std::make_shared<Scene>(SceneSerializer::LoadScene("scene.json"));
                    sceneManager.AddScene("MainScene", scene);
                    sceneManager.SetCurrentScene("MainScene");
                    player = scene->FindEntityByName("Player");
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    //SceneSerializer::SaveScene(*scene, "scene.json");
                }
                else if (event.key.code == sf::Keyboard::P)
                {
                    // Add functionality for 'P' key if needed
                }
				else if (event.key.code == sf::Keyboard::G)
				{
					physicsEngine.SetGravity(Vector2(physicsEngine.GetGravity().x, physicsEngine.GetGravity().y + 1));
					std::cout << "Gravity: " << physicsEngine.GetGravity().y << std::endl;
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
        std::shared_ptr<RectangleBody> rigidbody = player->GetComponent<RigidBodyComponent>()->GetBodyPtr();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            std::cout << "Angle: " << Vector2(0, -1).GetAngle() << std::endl;
            if (Physics::RayCast(player->GetTransform()->GetPosition(), { 0,-1 }, 70, rigidbody))
            {
                player->GetComponent<RigidBodyComponent>()->GetBody().ApplyForce(Vector2(0, -1000));
            }



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


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(true);
            rigidbody->SetVelocity({ -100, rigidbody->GetVelocity().y });
            //player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
            player->GetComponent<SpriteComponent>()->Flip(false);
            rigidbody->SetVelocity({ 100, rigidbody->GetVelocity().y });
           // player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
        }
        else
        {
            rigidbody->SetVelocity({ 0, rigidbody->GetVelocity().y });
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

        window.display();
    }
}
