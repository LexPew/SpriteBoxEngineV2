#pragma once
#include <fstream>
#include <iostream>
#include <thread>
#include <cereal/archives/json.hpp>

#include "Sprite.h"

#include "cereal/archives/binary.hpp"
#include "ECS/Entity.h"
#include "ECS/RigidBodyComponent.h"
#include "ECS/SpriteComponent.h"
#include "ECS/TransformComponent.h"
#include "Maths/Vector2.h"
#include "ECS/CamSys/FancyCameraComponent.h"
#include "Graphics/Renderer.h"
#include "Maths/Rect.h"


inline void RunCerealTest()
{
    // Cereal 
    std::cout << "CerealTest" << std::endl;

    AssetManager assetManager;
    assetManager.SetAssetRoot("Engine/assets");
    assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

    Physics physics;
    Physics::GetInstance()->SetGravity({ 0, 5 });

    // Vector Serialization test --WORKING
    Vector2 vec(1, 2);

    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss);
        oarchive(vec);
    }
    {
        Vector2 newVec;
        cereal::BinaryInputArchive iarchive(ss);
        iarchive(newVec);
        std::cout << newVec.x << " " << newVec.y << std::endl;
    }

    // Transform Component Serialization test --WORKING
    auto transform = std::make_shared<TransformComponent>();
    transform->SetPosition(Vector2(1, 2));
    transform->SetScale(Vector2(3, 4));

    std::stringstream ss2;
    {
        cereal::BinaryOutputArchive oarchive(ss2);
        oarchive(transform);
    }
    {
        std::shared_ptr<TransformComponent> newTransform;
        cereal::BinaryInputArchive iarchive(ss2);
        iarchive(newTransform);
        std::cout << newTransform->GetPosition().x << " " << newTransform->GetPosition().y << std::endl;
        std::cout << newTransform->GetScale().x << " " << newTransform->GetScale().y << std::endl;
    }

    // SpriteComponent Serialization test --WORKING
    Sprite sprite("Adventurer", AssetManager::GetInstance());

    auto spriteComponent = std::make_shared<SpriteComponent>();
    spriteComponent->sprite = sprite;
    spriteComponent->flipped = true;
    spriteComponent->currentAnimation = "Attack";

    std::stringstream ss3;
    {
        cereal::BinaryOutputArchive oarchive(ss3);
        oarchive(spriteComponent);
    }
    {
        std::shared_ptr<SpriteComponent> newSpriteComponent;
        cereal::BinaryInputArchive iarchive(ss3);
        iarchive(newSpriteComponent);
        std::cout << newSpriteComponent->currentAnimation << " " << newSpriteComponent->flipped << std::endl;
    }

    // RawCameraComponent Serialization test --WORKING
    auto camera = std::make_shared<RawCameraComponent>(Vector2(960, 540));

    // RigidBodyComponent Serialization test --WORKING
    auto rigidBody = std::make_shared<RigidBodyComponent>(100, 0, Rect(0, 0, 100, 100));

    // Entity Serialization test --WORKING
    auto entity = std::make_shared<Entity>("TestEntity");
    // Entities come with a transform component by default
    entity->GetTransform()->SetPosition(Vector2(1, 2));
    entity->GetTransform()->SetScale(Vector2(3, 4));
    entity->AddComponent(rigidBody);
    entity->AddComponent(camera);
    entity->AddComponent(spriteComponent);

    // Serialize
    {
        std::ofstream os("testEntity.cereal", std::ios::binary);
        cereal::BinaryOutputArchive oarchive(os);
        oarchive(entity);
    }

    // Deserialize
    std::shared_ptr<Entity> newEntity;
    {
        std::ifstream is("testEntity.cereal", std::ios::binary);
        cereal::BinaryInputArchive iarchive(is);
        iarchive(newEntity);
    }

    std::cout << "CerealTest Complete, Hopefully enjoy" << std::endl;

    // Quick render test
    sf::RenderWindow window(sf::VideoMode(960, 540), "CerealTest");

    Renderer renderer(&window);
    newEntity->Start();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            newEntity->GetComponent<FancyCameraComponent>()->AddCameraShake(100, 100, 1);
        }

        newEntity->Update(.033f);
        physics.Update(.033f);

        newEntity->Render(renderer);
        window.display();
    }
}

