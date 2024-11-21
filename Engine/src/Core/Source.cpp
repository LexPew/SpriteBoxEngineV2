#include <SFML/Graphics.hpp>
#include "Core/AssetManager.h"
#include "Core/Sprite.h"

int main()
{
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite JSON Test");

    // Create AssetManager and load sprite JSON
    AssetManager assetManager;
    assetManager.LoadSprite("C:/Users/James/source/repos/SpriteBoxEngine/Engine/assets/Sprites/TemplateAssets/Knight/Knight_Idle.json");

    // Create sprite
    Sprite playerSprite("Knight_Idle", assetManager);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear();

        // Play the "run" animation and draw the sprite
        playerSprite.PlayAnimation("Idle", deltaTime);

        playerSprite.Draw(window, 200.0f, 50.0f);
        playerSprite.Draw(window, 250.0f, 50.0f);
        window.display();
    }

    return 0;
}
