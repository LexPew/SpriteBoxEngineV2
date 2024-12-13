#pragma once

#include <iostream>


#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/ECS/CharacterActor.h"
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
	inputManager.RegisterKey(sf::Keyboard::Key::W);

	//Create the renderer and window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Small Game Test");
	Renderer renderer(&window);

	//Create the scene
	std::shared_ptr<Scene> smallGameTestScene = std::make_shared<Scene>();



	auto player = std::make_shared<CharacterActor>("Player2", Vector2(100, 0), Vector2(2, 2));
	player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
	const Vector2 spriteBounds = renderer.GetSpriteBounds(assetManager.GetSprite("Adventurer"));
	player->SetRect({ 0,0,spriteBounds.y, spriteBounds.y });
	player->AddComponent(std::make_shared<FancyCameraComponent>(Vector2(800, 600)));
	//Set the origin offset
	player->SetOriginOffset({- spriteBounds.y / 2, -spriteBounds.y / 2 });

	

	//Create the floor entity
	auto floor = std::make_shared<Solid>("Floor", Vector2(0, 30), Vector2(1, 1), Rect(0,0,64,600));

	//Add the entities to the scene
	smallGameTestScene->AddEntity(player);
	smallGameTestScene->AddEntity(floor);

	//Delta time clock
	sf::Clock deltaClock;

	//DEBUG STUFF
	//Collision debug
	sf::RectangleShape collisionRect;
	collisionRect.setFillColor(sf::Color::Transparent);
	collisionRect.setOutlineColor(sf::Color::Red);
	collisionRect.setOutlineThickness(1.0f);

	SceneManager::instance.SetCurrentScene(smallGameTestScene);

	//---> Game Loop <---//

	smallGameTestScene->Start();
	window.setFramerateLimit(30);
	while (window.isOpen())
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

		if (inputManager.IsHeld(sf::Keyboard::A))
		{

			player->SetVelocityX(-150);
			player->GetComponent<SpriteComponent>()->Flip(true);
			//player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(-100, 0) * deltaTime);
		}
		else if (inputManager.IsHeld(sf::Keyboard::D))
		{


			player->SetVelocityX(150);
			player->GetComponent<SpriteComponent>()->Flip(false);

			// player->GetTransform()->SetPosition(player->GetTransform()->GetPosition() + Vector2(100, 0) * deltaTime);
		}
		else if(player->IsGrounded())
		{
			player->SetVelocityX(0);
		}
		if (inputManager.IsPressed(sf::Keyboard::W))
		{
			player->Jump();
		}


		//---> Update <---//

		//Handle player anim states

		if (!player->IsGrounded())
		{
			player->GetComponent<SpriteComponent>()->PlayAnimation("Jump");
		}
		else if (player->GetVelocityX() != 0)
		{

			player->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
		}
		else
		{
			player->GetComponent<SpriteComponent>()->PlayAnimation("Idle");
		}

			
		//player->MoveY(10 * deltaTime, nullAction);
		smallGameTestScene->Update(deltaTime);


		//---> Render <---//

		smallGameTestScene->Render(renderer);
		//for (auto actor : smallGameTestScene->GetActors())
		//{
		//	
		//	collisionRect.setSize({ actor->GetRect().Width, actor->GetRect().Height });
		//	collisionRect.setPosition(actor->GetRect().Left, actor->GetRect().Top);
		//	window.draw(collisionRect);
		//}
		//for (auto solid : smallGameTestScene->GetSolids())
		//{
		//	collisionRect.setSize({ solid->solidRect.Width, solid->solidRect.Height });
		//	collisionRect.setPosition(solid->solidRect.Left, solid->solidRect.Top);
		//	window.draw(collisionRect);
		//}
		window.display();
	}

	SceneManager::SaveScene(smallGameTestScene, "SmallGameTestScene.scene");


}
