#include "Core/InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}
void InputManager::Update()
{
	for (auto& [key, keyState] : keyStateMap)
	{
		keyStateMap[key] = sf::Keyboard::isKeyPressed(key);
	}
}


bool InputManager::IsPressed(sf::Keyboard::Key p_key)
{
	return sf::Keyboard::isKeyPressed(p_key) && !keyStateMap[p_key];
}

bool InputManager::IsHeld(sf::Keyboard::Key p_key)
{
	return sf::Keyboard::isKeyPressed(p_key);
}

bool InputManager::IsReleased(sf::Keyboard::Key p_key)
{
	return sf::Keyboard::isKeyPressed(p_key) && keyStateMap[p_key];
}

void InputManager::RegisterKey(sf::Keyboard::Key p_key)
{
	keyStateMap[p_key] = false;
}

