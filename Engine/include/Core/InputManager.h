#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class InputManager
{
private:
	std::unordered_map<sf::Keyboard::Key, bool> keyStateMap;
public:
	InputManager();
	~InputManager();
	void Update();
	bool IsPressed(sf::Keyboard::Key p_key);
	bool IsHeld(sf::Keyboard::Key p_key);
	bool IsReleased(sf::Keyboard::Key p_key);
	void RegisterKey(sf::Keyboard::Key p_key);
};

