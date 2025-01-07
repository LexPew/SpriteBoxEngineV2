#pragma once
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

#include "Maths/Vector2.h"
//Class: InputManager
//Purpose: A class that manages input from the keyboard
class InputManager
{
private:
	static InputManager* instance; //Holds the instance of the input manager

	std::unordered_map<sf::Keyboard::Key, bool> currentKeyState; // The current state of the keys (this frame)
	std::unordered_map<sf::Keyboard::Key, bool> previousKeyState; // The previous state of the keys (last frame)


	//Mouse keys
	Vector2 mousePosition{ 0,0 }; // The current mouse position
	bool leftMouseClick{ false };
	bool rightMouseClick{ false };
	bool middleMouseClick{ false };
	float scrollWheelDelta{ 0.0f };

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

	//Mouse functions


	/**
	 * @brief Update the scroll delta
	 * @param p_scrollWheelDelta The current mouse scroll delta
	 */
	void UpdateScrollWheelDelta(const float p_scrollWheelDelta) { scrollWheelDelta += p_scrollWheelDelta; }

	/**
	 * @brief Get the current mouse position
	 * @return The current mouse position
	 */
	const Vector2& GetMousePosition() const { return mousePosition; }

	/**
	 * @brief Check if the left mouse button was clicked
	 * @return Whether the left mouse button was clicked
	 */
	const bool LeftMouseButtonClicked() const { return leftMouseClick; }

	/**
	 * @brief Check if the right mouse button was clicked
	 * @return Whether the right mouse button was clicked
	*/
	const bool RightMouseButtonClicked() const { return rightMouseClick; }

	/**
	* @brief Check if the middle mouse button was clicked
	* @return Whether the middle mouse button was clicked
	*/
	const bool MiddleMouseButtonClicked() const { return middleMouseClick; }

	/**
	 * @brief Get the scroll wheel delta
	* @return The scroll wheel delta
	*/
	const float GetScrollWheelDelta() const { return scrollWheelDelta; }

};




