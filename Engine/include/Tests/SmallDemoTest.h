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
	physicsEngine.SetGravity({ 0, 80 });
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
	auto player = std::make_shared<Entity>("Player", Vector2(100, 100), Vector2(2, 2));
	player->AddComponent(std::make_shared<SpriteComponent>("Adventurer", assetManager));
	const Vector2 spriteBounds = renderer.GetSpriteBounds(assetManager.GetSprite("Adventurer"));
	player->AddComponent(std::make_shared<RigidBodyComponent>(1.0f, 0.2f, Rect(0, 0, 100, 100)));
	player->AddComponent(std::make_shared<FancyCameraComponent>(Vector2(800, 600)));

	//Create the floor entity
	auto floor = std::make_shared<Entity>("Floor", Vector2(0, 400), Vector2(1, 1));
	floor->AddComponent(std::make_shared<RigidBodyComponent>(0.0f, 0.2f, Rect(0, 0, 64, 500)));

	//Add the entities to the scene
	smallGameTestScene.AddEntity(player);
	smallGameTestScene.AddEntity(floor);

	//Delta time clock
	sf::Clock deltaClock;

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


		//---> Input <---//

		inputManager.Update();
		std::shared_ptr<RigidBodyComponent> r = player->GetComponent<RigidBodyComponent>();
		if (inputManager.IsHeld(sf::Keyboard::Key::A))
		{
			std::cout << "A key is pressed" << std::endl;
			r->GetBody().SetVelocity({ -200, r->GetBody().GetVelocity().y });
		}
		else if (inputManager.IsHeld(sf::Keyboard::Key::D))
		{
			std::cout << "D key is pressed" << std::endl;
			r->GetBody().SetVelocity({ 200, r->GetBody().GetVelocity().y });
		}
		else
		{
			r->GetBody().SetVelocity({ 0, r->GetBody().GetVelocity().y });
		}


		//---> Update <---//



		smallGameTestScene.Update(deltaTime);
		physicsEngine.Update(deltaTime);


		//---> Render <---//

		smallGameTestScene.Render(renderer);
		window.display();
	}

	SceneSerializer::SaveScene(smallGameTestScene, "SmallGameTestScene.json");


}
