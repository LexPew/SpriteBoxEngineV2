#pragma once

#include <iostream>
#ifdef _WIN32
#define NOMINMAX //Stops windows from overriding min and max in std
#define NODRAWTEXT //Disables DrawText
#include <Windows.h>
#endif

//Class: DebugMacros
//Purpose: A collection of macros for debugging and logging messages
#ifdef _DEBUG

/**
 * @brief Logs a message to the console.
 * @param message The message to log.
 */
#define DEBUG_LOG(message) std::cout << message << std::endl

/**
 * @brief Logs an error message to the console.
 * @param message The error message to log.
 */
#define DEBUG_LOG_ERROR(message) std::cerr << message << std::endl

/**
 * @brief Draws a rectangle to the screen for debugging purposes.
 * @param renderer The renderer responsible for drawing.
 * @param rect The rectangle to be drawn.
 * @param color The color of the rectangle.
 */
#define DEBUG_DRAW_RECT(renderer, rect, color) renderer.DrawRect(rect, color)

/**
 * @brief Draws a point to the screen for debugging purposes.
 * @param renderer The renderer responsible for drawing.
 * @param point The point to be drawn.
 * @param color The color of the point.
 */
#define DEBUG_DRAW_POINT(renderer, point, color) renderer.DrawPoint(point, color)

#else

#define DEBUG_LOG(message)
#define DEBUG_LOG_ERROR(message)
#define DEBUG_DRAW_RECT(renderer, rect, color)
#define DEBUG_DRAW_POINT(renderer, point, color)

#endif

#ifdef _WIN32

/**
 * @brief Displays a Windows dialog box with a message.
 * @param message The message to display in the dialog box.
 * @note Put L in front of the string to make it a wide string literal.
 */
#define DEBUG_SHOW_WINDOWS_DIALOG_BOX(message) MessageBox(NULL, message, L"Error", MB_OK)

#else

#define DEBUG_SHOW_WINDOWS_DIALOG_BOX(message)

#endif

// COLOR MACROS
/**
 * @brief Debug color: Semi-transparent green.
 */
#define DEBUG_STGREEN sf::Color(0, 255, 0, 100)

/**
 * @brief Debug color: Semi-transparent red.
 */
#define DEBUG_STRED sf::Color(255, 0, 0, 100)
	