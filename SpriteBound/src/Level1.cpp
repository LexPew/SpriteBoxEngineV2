// SpriteBound/src/Level1.cpp

#include "Level1.h"
#include "Core/SceneManager.h"
#include "Core/ECS/SpriteSolid.h"

Level1::Level1()
{
    CreateLevel();
}





void Level1::CreateLevel()
{
    SetSceneName("Level1");
    // Set the asset root directory
    AssetManager::GetInstance().SetAssetRoot("SpriteBound/assets");

    // Load required assets
    AssetManager::GetInstance().LoadSprite("sprites/Adventurer.json");
    AssetManager::GetInstance().LoadSprite("sprites/Grass_Platform.json");
    AssetManager::GetInstance().LoadSprite("sprites/Grass_PlatformShort.json");
    AssetManager::GetInstance().LoadSprite("sprites/Goal.json");

    // Load and add parallax background layers
    for (int i = 1; i < 6; i++)
    {
        std::string textureId = "PB" + std::to_string(i);
        std::string texturePath = "sprites/parallaxbackground/" + std::to_string(i) + ".png";
        AssetManager::GetInstance().LoadTexture(textureId, texturePath);
        Renderer::GetInstance().AddBackgroundLayer(textureId, static_cast<float>(i));
    }

    // Create the player
    auto player = std::make_shared<PlayerActor>("Player", Vector2::Zero(), Vector2::One(), "Adventurer");
    AddEntity(player);

    // Set the origin offset
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed for randomness

    // Ensure the first platform is below the player
    Vector2 firstPlatformPosition(0, 100); // Position the first platform below the player
    Vector2 firstPlatformScale(1.0f, 1.0f);
    auto firstPlatform = std::make_shared<SpriteSolid>("Floor", firstPlatformPosition, firstPlatformScale, "Grass_Platform", false);
    AddEntity(firstPlatform);

	// Generate the rest of the platforms with random positions and scales, and a random number of platforms
	int numberOfPlatforms = std::rand() % 10 + 5; // Randomize the number of platforms between 5 and 15
    for (int i = 1; i < numberOfPlatforms; i++)
    {
        float xPos = 200 * i + (std::rand() % 100 - 50); // Randomize x position slightly
        float yPos = 50 + (std::rand() % 100 - 50); // Randomize y position slightly
        Vector2 position(xPos, yPos);
        Vector2 scale(1.0f + static_cast<float>(std::rand() % 50) / 100.0f, 1.0f); // Randomize scale slightly

        // Randomly choose between the two platform types
        std::string platformType = (std::rand() % 2 == 0) ? "Grass_Platform" : "Grass_PlatformShort";
        auto platform = std::make_shared<SpriteSolid>("Floor", position, scale, platformType, false);
        AddEntity(platform);

        // If we are creating the last platform then add another solid as a trigger on top of it
        if (i == numberOfPlatforms - 1)
        {
            Vector2 triggerPosition = position;
            triggerPosition.y -= 50;
            auto trigger = std::make_shared<SpriteSolid>("Trigger", triggerPosition, Vector2(1.0f, 1.0f), "Goal", true);
            trigger->onTriggerEnter.Bind(&Level1::OnFinishTrigger, this);
            AddEntity(trigger);
        }
		reloadScene = false;
        Awake();
		Start();
    }

}

void Level1::Update(float deltaTime)
{
    // Update the base scene
    Scene::Update(deltaTime);

    if (reloadScene)
    {
        reloadScene = false;
        ResetLevel();
    }

    // Additional update logic if needed
}

void Level1::OnFinishTrigger(Actor& p_actor)
{
    // Handle the finish trigger
    std::cout << "Finish Trigger activated! Restarting level..." << std::endl;

    // Reload the level
    reloadScene = true;
}

void Level1::ResetLevel()
{
    Clean();
	CreateLevel();
}
