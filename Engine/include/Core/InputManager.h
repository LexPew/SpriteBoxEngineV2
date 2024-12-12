#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

class InputManager {
public:
    void RegisterKey(sf::Keyboard::Key key);
    void Update();
    bool IsPressed(sf::Keyboard::Key key) const;
    bool IsHeld(sf::Keyboard::Key key) const;
    bool IsReleased(sf::Keyboard::Key key) const;

private:
    std::unordered_map<sf::Keyboard::Key, bool> currentKeyState;
    std::unordered_map<sf::Keyboard::Key, bool> previousKeyState;
};

