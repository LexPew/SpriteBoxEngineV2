#pragma once

#include <iostream>


#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Core/Scene.h"
#include "Core/SceneSerializer.h"
#include "Core/ECS/RigidBodyComponent.h"
#include "Core/ECS/SpriteComponent.h"
#include "Core/ECS/CamSys/FancyCameraComponent.h"
#include "Graphics/Renderer.h"
#include "Physics/Impulse2DLite.h"
#include "SFML/Graphics.hpp"

void inline SmallGameTest()
{
	//---> Small Game Test <---//

	// Create the asset manager
	AssetManager assetManager;
	assetManager.SetAssetRoot("Engine/assets");
	assetManager.LoadSprite("Sprites/TemplateAssets/Adventurer.json");

	//Create the physics engine
	Physics physicsEngine;
	physicsEngine.SetGravity({ 0, 50 });
	physicsEngine.SetGroundedGravity({ 0, 1 });

	//Create the input manager
	InputManager inputManager;
	inputManager.RegisterKey(sf::Keyboard::Key::A);
	inputManager.RegisterKey(sf::Keyboard::Key::D);

	//Create the renderer and window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Small Game Test");
	Renderer renderer(&window);

	//Create the scene
	Scene smallGameTestScene;

	//Create the player entity
	auto player = std::make_shared<Entity>("Player", Vector2(100, 0), Vector2(2, 2));
	player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
	const Vector2 spriteBounds = renderer.GetSpriteBounds(assetManager.GetSprite("Adventurer"));

	player->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0, 0, spriteBounds.y, spriteBounds.x)));
	player->AddComponent(std::make_shared<FancyCameraComponent>(Vector2(800, 600)));

	//Create the floor entity
	auto floor = std::make_shared<Entity>("Floor", Vector2(0, 800), Vector2(1, 1));
	floor->GetTransform()->SetPosition({ 0,600 });
	floor->AddComponent(std::make_shared<RigidBodyComponent>(0.0f, 0.2f, Rect(0, 0, 64, 500)));

	//Add the entities to the scene
	smallGameTestScene.AddEntity(player);
	smallGameTestScene.AddEntity(floor);

	//Delta time clock
	sf::Clock deltaClock;

	//DEBUG STUFF
	//Collision debug
	sf::RectangleShape collisionRect;
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setOutlineThickness(1.0f);


	//---> Game Loop <---//
	
	smallGameTestScene.Start();

	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		float deltaTime = deltaClock.restart().asSeconds();

		//---> Physics <---//
		physicsEngine.Update(deltaTime);


		//---> Input <---//

		inputManager.Update();
		std::shared_ptr<RectangleBody> r = player->GetComponent<RigidBodyComponent>()->GetBodyPtr();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
			player->GetComponent<SpriteComponent>()->Flip(true);
			r->SetVelocity({ -100, r->GetVelocity().y });
			//player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
			player->GetComponent<SpriteComponent>()->Flip(false);
			r->SetVelocity({ 100, r->GetVelocity().y });
			// player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
		}
		else
		{
			player->GetComponent<SpriteComponent>()->PlayAnimation("Idle");

			r->SetVelocity({ 0, r->GetVelocity().y });
		}


		//---> Update <---//



		smallGameTestScene.Update(deltaTime);


		//---> Render <---//

		smallGameTestScene.Render(renderer);
		for (auto entity : smallGameTestScene.GetEntities())
		{
			std::shared_ptr<RigidBodyComponent> rigidBody = entity->GetComponent<RigidBodyComponent>();
			if(rigidBody)
			{
				collisionRect.setSize(sf::Vector2f(rigidBody->GetBody().GetRect().Width, rigidBody->GetBody().GetRect().Height));
				collisionRect.setPosition(rigidBody->GetBody().GetPosition().x, rigidBody->GetBody().GetPosition().y);
				window.draw(collisionRect);
			}
		}
		window.display();
	}

	SceneSerializer::SaveScene(smallGameTestScene, "SmallGameTestScene.json");


}
