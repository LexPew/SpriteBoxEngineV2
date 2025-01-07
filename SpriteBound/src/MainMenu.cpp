// SpriteBound/src/MainMenu.cpp

#include "MainMenu.h"

#include "Level1.h"
#include "Core/InputManager.h"
#include "Core/SceneManager.h"
#include "Core/ECS/UI/UILabel.h"

MainMenu::MainMenu()
{
    CreateMenu();
}

void MainMenu::CreateMenu()
{
    // Set the asset root directory
    AssetManager::GetInstance().SetAssetRoot("SpriteBound/assets");

    // Load required assets
    AssetManager::GetInstance().LoadFont("default", "fonts/PixelifySans-Regular.ttf");
    AssetManager::GetInstance().LoadSprite("sprites/Button.json");
    AssetManager::GetInstance().LoadSound("OnClick", "sounds/kenny/select_001.ogg");

    // Load and add parallax background layers
    for (int i = 1; i < 6; i++)
    {
        std::string textureId = "PB" + std::to_string(i);
        std::string texturePath = "sprites/parallaxbackground/" + std::to_string(i) + ".png";
        AssetManager::GetInstance().LoadTexture(textureId, texturePath);
        Renderer::GetInstance().AddBackgroundLayer(textureId, static_cast<float>(i));
    }

    // Get window size
    auto windowSize = Renderer::GetInstance().GetWindow()->getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);

    // Calculate positions for centering and spacing
    const float buttonWidth = 256.0f;
    const float buttonHeight = 88.0f;
    const float centerX = windowWidth / 2.0f;
    const float centerY = windowHeight / 2.0f;
    const float titleY = 100.0f;
    const float playButtonY = centerY - buttonHeight;
    const float exitButtonY = centerY + buttonHeight;
    // Create title entity with UILabel component
    auto titleEntity = std::make_shared<Entity>("Title", Vector2(centerX, titleY), Vector2::One());
    auto titleLabel = std::make_shared<UILabel>(
        TextData("SPRITEBOUND", 80, { 255,255,255,255 }, "default")
    );
    titleEntity->AddComponent(titleLabel);
    AddEntity(titleEntity);

    // Create the Play button entity with UIButton component
    auto playEntity = std::make_shared<Entity>("PlayButton", Vector2(centerX, playButtonY), Vector2::One());
    auto playButton = std::make_shared<UIButton>(
        []() { auto lvl1 = std::make_shared<Level1>(); lvl1->SetSceneName("Level 1"); SceneManager::GetInstance().SetCurrentScene(lvl1); },
        TextData("PLAY", 30, { 255,255,255,255 }, "default"),
        AssetManager::GetInstance().GetSprite("Button"),
        "OnClick"
    );
    playEntity->AddComponent(playButton);
    AddEntity(playEntity);

    // Create the Exit button entity with UIButton component
    auto exitEntity = std::make_shared<Entity>("ExitButton", Vector2(centerX, exitButtonY), Vector2::One());
    auto exitButton = std::make_shared<UIButton>(
        []() { Renderer::GetInstance().GetWindow()->close(); },
        TextData("EXIT", 30, { 255,255,255,255 }, "default"),
        AssetManager::GetInstance().GetSprite("Button"),
        "OnClick"
    );
    exitEntity->AddComponent(exitButton);
    AddEntity(exitEntity);

    // Initialize the scene
    Awake();
    Start();
}

void MainMenu::Update(const float deltaTime)
{
    // Update the base scene
    Scene::Update(deltaTime);

    // Retrieve mouse position
    Vector2 mousePos = InputManager::GetInstance().GetMousePosition();

    // Get window width for parallax calculation
    float windowWidth = static_cast<float>(Renderer::GetInstance().GetWindow()->getSize().x);

    // Calculate parallax offset based on mouse position
    parallaxOffset.x = (mousePos.x / windowWidth) * parallaxRange;

    // Update background position in Renderer
    Renderer::GetInstance().SetBackGroundPosition(parallaxOffset);
}
