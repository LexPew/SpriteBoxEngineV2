// InputManager.cpp
#include "Core/InputManager.h"

void InputManager::RegisterKey(sf::Keyboard::Key key) {
    currentKeyState[key] = false;
    previousKeyState[key] = false;
}

void InputManager::Update() {
    for (auto& keyState : currentKeyState) {
        previousKeyState[keyState.first] = keyState.second;
        keyState.second = sf::Keyboard::isKeyPressed(keyState.first);
    }
}

bool InputManager::IsPressed(sf::Keyboard::Key key) const {
    auto it = currentKeyState.find(key);
    if (it != currentKeyState.end()) {
        return it->second && !previousKeyState.at(key);
    }
    return false;
}

bool InputManager::IsHeld(sf::Keyboard::Key key) const {
    auto it = currentKeyState.find(key);
    if (it != currentKeyState.end()) {
        return it->second;
    }
    return false;
}

bool InputManager::IsReleased(sf::Keyboard::Key key) const {
    auto it = currentKeyState.find(key);
    if (it != currentKeyState.end()) {
        return !it->second && previousKeyState.at(key);
    }
    return false;
}
