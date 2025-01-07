// InputManager.cpp
#include "Core/InputManager.h"

#include <SFML/Window/Mouse.hpp>

InputManager* InputManager::instance{ nullptr };

void InputManager::RegisterKey(const sf::Keyboard::Key p_key) {
	//Check if the key is already registered
	if (currentKeyState.find(p_key) != currentKeyState.end()) {
		return;
	}

	// Register the key in the current and previous key state maps
    currentKeyState[p_key] = false;
    previousKeyState[p_key] = false;
}

void InputManager::Update() {
    // Mouse state update
    leftMouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    rightMouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    middleMouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

    // Update mouse position
	mousePosition.x = static_cast<float>(sf::Mouse::getPosition().x);
	mousePosition.y = static_cast<float>(sf::Mouse::getPosition().y);

	//Key state update
    for (auto& keyState : currentKeyState) {
        previousKeyState[keyState.first] = keyState.second;
        keyState.second = sf::Keyboard::isKeyPressed(keyState.first);
    }
}

bool InputManager::IsPressed(const sf::Keyboard::Key p_key) const {
    auto it = currentKeyState.find(p_key);
    if (it != currentKeyState.end()) {
        return it->second && !previousKeyState.at(p_key);
    }
    return false;
}

bool InputManager::IsHeld(const sf::Keyboard::Key p_key) const {
    auto it = currentKeyState.find(p_key);
    if (it != currentKeyState.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::IsReleased(const sf::Keyboard::Key p_key) const {
    auto it = currentKeyState.find(p_key);
    if (it != currentKeyState.end()) {
        return !it->second && previousKeyState.at(p_key);
    }
    return false;
}


