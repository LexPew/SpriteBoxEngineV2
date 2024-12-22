#pragma once
#include "Core/AssetManager.h"
#include "Core/InputManager.h"
#include "Core/Scene.h"
#include "Core/SceneManager.h"
#include "Core/ECS/PhysicsActor.h"
#include "Core/ECS/PlayerActor.h"
#include "Core/ECS/RigidBodyComponent.h"
#include "Core/ECS/SpriteComponent.h"
#include "Core/ECS/CamSys/FancyCameraComponent.h"
#include "Graphics/Renderer.h"
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
	inputManager.RegisterKey(sf::Keyboard::Key::R);
	//Create the renderer and window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Small Game Test");
	Renderer renderer(&window);

	//Create the scene
	std::shared_ptr<Scene> smallGameTestScene = std::make_shared<Scene>();



	auto player = std::make_shared<PlayerActor>("Player", Vector2::Zero(), Vector2::One(), "Adventurer");
	//Set the origin offset


	


	for (int i = 0; i < 10; i++)
	{
		auto platform = std::make_shared<Solid>("Platform" + std::to_string(i), Vector2(150 * i, 200), 
			Vector2(1, 1), Rect(0, 0, 64, 64));
		smallGameTestScene->AddEntity(platform);
	}

	//Add the entities to the scene
	smallGameTestScene->AddEntity(player);


	//Delta time clock
	sf::Clock deltaClock;


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

		

		//---> Update <---//
	
		smallGameTestScene->Update(deltaTime);


		//---> Render <---//

		smallGameTestScene->Render(renderer);

		window.display();
	}

	SceneManager::SaveScene(smallGameTestScene, "SmallGameTestScene.scene");


}
