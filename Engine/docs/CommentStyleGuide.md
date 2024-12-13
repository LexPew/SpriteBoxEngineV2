# C++ Game Engine Commenting Guidelines

Effective comments are critical for maintaining a clean, understandable, and collaborative codebase. Follow these guidelines to ensure your comments add value and clarity to the project.

---

## 1. General Principles

### 1.1 Be Clear and Concise

- Write comments that are easy to understand, avoiding jargon unless it is domain-specific.
- Use proper grammar, punctuation, and spelling for clarity.

### 1.2 Comment Why, Not Just What

- Explain the reasoning behind non-obvious code, such as design decisions, algorithm choices, or workarounds for known issues.
- Avoid restating what the code does unless it is complex.

**Example:**
```cpp
// Ensure game objects are sorted for efficient collision detection.
std::sort(gameObjects.begin(), gameObjects.end(), compareByPosition);
```

---

## 2. Comment Types and Usage

### 2.1 File-Level Comments

- Provide a brief overview of the file's purpose at the top of each file.

**Example:**
```cpp
// File: PhysicsEngine.cpp
// Description: Implements the physics engine for handling object motion, collisions,
//              and rigid body dynamics in the game world.
```

### 2.2 Class-Level Comments

- Describe the purpose and usage of a class, highlighting key features and responsibilities.

**Example:**
```cpp
// Class: GameObject
// Purpose: Represents an entity in the game world, providing position, rotation, and
//          lifecycle management functionality.
```

### 2.3 Function/Method-Level Comments

- Use comments to explain the function's purpose, input parameters, return values, and exceptions it may throw.

**Example:**
```cpp
* @brief Loads a texture from a file into GPU memory.
* @param filePath Path to the texture file.
* @return TextureHandle A handle to the loaded texture.
* @throws std::runtime_error if the file cannot be loaded.
*/
TextureHandle loadTexture(const std::string& filePath);
```

### 2.4 Inline Comments

- Use inline comments sparingly to clarify complex or non-obvious logic.

**Example:**
```cpp
while (currentNode != nullptr) {
    // Break the loop if a cycle is detected.
    if (visitedNodes.count(currentNode)) {
        break;
    }
    visitedNodes.insert(currentNode);
    currentNode = currentNode->next;
}
```

---

## 3. Style Guidelines

### 3.1 Use Consistent Formatting

- Begin comments with a capital letter.
- End comments with a period for full sentences.

### 3.2 Avoid Redundant Comments

- Do not add comments that simply state the obvious or restate the code.

**Avoid:**
```cpp
int health = 100; // Set health to 100.
```
**Better:**
```cpp
int health = 100; // Initial player health.
```

### 3.3 Use TODO/FIXME/NOTE Tags

- Use these tags to highlight areas needing attention or improvement.

**Example:**
```cpp
// TODO: Optimize this loop to reduce frame drops on large maps.
```

---

## 4. Commenting Best Practices

### 4.1 Keep Comments Up-to-Date

- Regularly update comments to match the code as it evolves.
- Remove outdated comments to avoid confusion.

### 4.2 Use Documentation Tools

- Write comments in a format compatible with tools like Doxygen to auto-generate documentation.

**Example:**
```cpp
/**
 * Updates the position of the player character.
 *
 * @param deltaTime Time elapsed since the last frame.
 */
void updatePosition(float deltaTime);
```

### 4.3 Avoid Overloading Comments

- Do not include too much detail that might overwhelm the reader. Focus on providing context and clarity.

---

## 5. Review and Feedback

- Review comments during code reviews for accuracy, clarity, and relevance.
- Encourage team members to provide constructive feedback on comments.

---

By following these commenting guidelines, we aim to create a codebase that is intuitive, maintainable, and welcoming for all contributors. Comments should serve as a bridge between the developer’s intent and the reader’s understanding.

**Happy coding!**

