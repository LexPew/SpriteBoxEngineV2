#pragma once
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

#include "Core/InputManager.h"

void inline InputSystemTest()
{
	// Create a new input manager
	InputManager inputManager;
	// Register the keys we want to use
	inputManager.RegisterKey(sf::Keyboard::Key::A);
	inputManager.RegisterKey(sf::Keyboard::Key::B);
	inputManager.RegisterKey(sf::Keyboard::Key::C);
	inputManager.RegisterKey(sf::Keyboard::Key::Escape);
	// Loop until the exit key is pressed
	while (!inputManager.IsPressed(sf::Keyboard::Escape))
	{
		// Update the input manager
		inputManager.Update();
		// Check if the A key is pressed
		if (inputManager.IsPressed(sf::Keyboard::Key::A))
		{
			std::cout << "A key is pressed" << std::endl;
		}
		// Check if the B key is held
		if (inputManager.IsHeld(sf::Keyboard::Key::B))
		{
			std::cout << "B key is held" << std::endl;
		}
		// Check if the C key is released
		if (inputManager.IsReleased(sf::Keyboard::Key::C))
		{
			std::cout << "C key is released" << std::endl;
		}
	}
	
}
