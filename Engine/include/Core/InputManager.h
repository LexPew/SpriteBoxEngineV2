#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>
//Class: InputManager
//Purpose: A class that manages input from the keyboard
class InputManager
{
private:
	static InputManager* instance; //Holds the instance of the input manager

	std::unordered_map<sf::Keyboard::Key, bool> currentKeyState; // The current state of the keys (this frame)
	std::unordered_map<sf::Keyboard::Key, bool> previousKeyState; // The previous state of the keys (last frame)
public:
	

	//Construct a new InputManager object
	InputManager()
	{
		if (instance == nullptr)
		{
			instance = this;
		}
	}
	~InputManager()
	{

		instance = nullptr;
		currentKeyState.clear();
		previousKeyState.clear();

	}

	static InputManager& GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new InputManager();
		}
		return *instance;
	}
	/**
	 * @brief Register a key to be tracked by the input manager
	 * @param p_key The key to register
	 */
    void RegisterKey(sf::Keyboard::Key p_key);
	/**
	 * @brief Update the input manager
	 */
    void Update();
	/**
	 * @brief Check if a key is pressed
	 * @param p_key Key to check
	 * @return Whether the key is pressed
	 */
	bool IsPressed(sf::Keyboard::Key p_key) const;
	/**
	 * @brief Check if a key is held
	 * @param p_key Key to check
	 * @return Whether the key is held
	*/
    bool IsHeld(sf::Keyboard::Key p_key) const;
	/**
	 * @brief Check if a key was released this frame
	 * @param p_key Key to check
	 * @return Whether the key was released this frame
	*/
    bool IsReleased(sf::Keyboard::Key p_key) const;


};




