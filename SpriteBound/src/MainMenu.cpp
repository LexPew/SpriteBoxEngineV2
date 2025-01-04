#include "MainMenu.h"

#include "Core/SceneManager.h"

MainMenu::MainMenu()
{
	CreateMenu();
}
void MainMenu::CreateMenu()
{
    // Load the font and sprite
    AssetManager::GetInstance().SetAssetRoot("SpriteBound/assets");
    AssetManager::GetInstance().LoadFont("default", "fonts/PixelifySans-Regular.ttf");
    AssetManager::GetInstance().LoadSprite("sprites/Button.json");
    AssetManager::GetInstance().LoadTexture("MBG", "textures/background.png");
    AssetManager::GetInstance().LoadSound("OnClick", "sounds/kenny/select_001.ogg");
	Renderer::GetInstance().SetBackground("MBG");
    // Get window size
    auto windowSize = Renderer::GetInstance().GetWindow()->getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    // Calculate positions for centering and spacing
    float buttonWidth = 256.0f;
    float buttonHeight = 88.0f;
    float centerX = windowWidth / 2.0f;
	float centerY = windowHeight / 2.0f;
	float playButtonY = centerY - buttonHeight;
	float exitButtonY = centerY + buttonHeight;

    // Create the play button
    auto playEntity = std::make_shared<Entity>("PlayButton", Vector2(centerX, playButtonY), Vector2::One());
    auto playButton = std::make_shared<UIButton>([]() { DEBUG_LOG("Play button clicked"); },
        TextData("PLAY", 30, { 255,255,255,255 },
            "default"),
        AssetManager::GetInstance().GetSprite("Button"), "OnClick");
    playEntity->AddComponent(playButton);
    AddEntity(playEntity);

    // Create the exit button
    auto exitEntity = std::make_shared<Entity>("ExitButton", Vector2(centerX, exitButtonY), Vector2::One());
    auto exitButton = std::make_shared<UIButton>([]() { DEBUG_LOG("Exit button clicked"); },
        TextData("EXIT", 30, { 255,255,255,255 },
            "default"),
        AssetManager::GetInstance().GetSprite("Button"), "OnClick");
    exitEntity->AddComponent(exitButton);
    AddEntity(exitEntity);

    Start();
}


