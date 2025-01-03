#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

// Class: Game
// Purpose: The main class of the game
class Game
{
private:
	sf::RenderWindow gameWindow;
	bool isRunning{ false };
	float deltaTime{ 0.0f };
	sf::Clock clock;
public:
	Game() = default;
	~Game() = default;

	
	bool Initialize();
	void Cleanup();

	void Loop();

	void HandleEvents();
	void Update();
	void Render();
};
