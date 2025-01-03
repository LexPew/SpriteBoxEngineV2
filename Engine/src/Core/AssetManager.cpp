#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Core/AssetManager.h"

#include "Debug/DebugMacros.h"


AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager()
{
    CreateNullSpriteData();
    LoadFallBackFont();
}

void AssetManager::CreateNullSpriteData()
{
    nullSpriteData.id = "NULL";
    nullSpriteData.spriteSheetRows = 1;
    nullSpriteData.spriteSheetColumns = 1;

    //Create a 64*64 checkerboard texture purple and black
    sf::Image image;
    image.create(64, 64, sf::Color::Magenta);
    for (int y = 0; y < 64; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if ((x + y) % 2 == 0)
            {
                image.setPixel(x, y, sf::Color::Black);
            }
        }
    }

    nullSpriteData.texture.loadFromImage(image);
}

void AssetManager::LoadFallBackFont()
{
    //Only works on windows
    //TODO: Add support for other operating systems or find a better way to load a default font
    if (!fallBackFont.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
    {
        DEBUG_SHOW_WINDOWS_DIALOG_BOX(L"Critical Error: Cannot load default font");
    }
    DEBUG_LOG("Loaded fall back font successfully");
}

std::string AssetManager::ResolvePath(const std::string& p_relativePath) const
{
    std::filesystem::path fullPath = assetRoot / p_relativePath;
    return fullPath.string();  // Return as std::filesystem::path
}

bool AssetManager::LoadSprite(const std::string& p_path)
{
    std::string path = ResolvePath(p_path);
    std::ifstream jsonFile(path);
    if (!jsonFile.is_open())
    {
        DEBUG_LOG_ERROR("Failed to open JSON file " << path);
        return false;
    }
    nlohmann::json jsonData;
    jsonFile >> jsonData;

    SpriteData spriteData;

    //General sprite things
    spriteData.id = jsonData["id"];
    spriteData.spriteSheetRows = jsonData["spriteSheetRows"];
    spriteData.spriteSheetColumns = jsonData["spriteSheetColumns"];

    //Load texture
    std::string texturePath = jsonData["texturePath"];
    if (!spriteData.texture.loadFromFile(ResolvePath(texturePath)))
    {
        DEBUG_LOG_ERROR("Failed to load texture: " << texturePath);
        return false;
    }

    //Loop through all animations and create new data structs for them to then add to the map in SpriteData
    for (auto& [animName, animDetails] : jsonData["animations"].items())
    {
        AnimationData animationData;
        animationData.startFrame = animDetails["startFrame"];
        animationData.endFrame = animDetails["endFrame"];
        animationData.frameDuration = animDetails["frameDuration"];
        spriteData.animations[animName] = animationData;
    }

    m_sprites.insert({ spriteData.id, spriteData });
    m_spritePaths.insert({ spriteData.id, p_path });
    return true;
}

bool AssetManager::LoadFont(const std::string& p_id, const std::string& p_path)
{
    std::string path = ResolvePath(p_path);
    sf::Font font;
    if (!font.loadFromFile(path))
    {
        DEBUG_LOG_ERROR("Failed to load font: " + path);
        return false;
    }
    m_fonts.insert({ p_id, font });
    m_fontPaths.insert({ p_id, p_path });
    return true;
}

bool AssetManager::LoadTexture(const std::string& p_id, const std::string& p_path)
{
    std::string path = ResolvePath(p_path);
    sf::Texture texture;
    if (!texture.loadFromFile(path))
    {
        DEBUG_LOG_ERROR("Failed to load texture: " + path);
        return false;
    }
    m_textures.insert({ p_id, texture });
    m_texturePaths.insert({ p_id, p_path });
    return true;
}

bool AssetManager::LoadSound(const std::string& p_id, const std::string& p_path)
{
    std::string path = ResolvePath(p_path);
    sf::SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile(path))
    {
        DEBUG_LOG_ERROR("Failed to load sound: " + path);
        return false;
    }
    m_soundBuffers.insert({ p_id, soundBuffer });
    m_soundPaths.insert({ p_id, p_path });
    return true;
}

const sf::Texture& AssetManager::GetTexture(const std::string& p_id) const
{
    if (m_textures.find(p_id) != m_textures.end())
    {
        return m_textures.find(p_id)->second;
    }
    DEBUG_LOG_ERROR("Failed to retrieve texture id: " << p_id);
    return nullSpriteData.texture;
}

const SpriteData& AssetManager::GetSprite(const std::string& p_id) const
{
    //If our unordered map contains 
    if (m_sprites.find(p_id) != m_sprites.end())
    {
        return m_sprites.find(p_id)->second;
    }
    //Handle if we are unable to find a sprite by returning the error sprite
    DEBUG_LOG_ERROR("Failed to retrieve sprite id: " << p_id);
    DEBUG_SHOW_WINDOWS_DIALOG_BOX(L"Failed to load sprite, please verify game files");
    return nullSpriteData;
}

const sf::Font& AssetManager::GetFont(const std::string& p_id) const
{
    if (m_fonts.find(p_id) != m_fonts.end())
    {
        return m_fonts.find(p_id)->second;
    }
    DEBUG_LOG_ERROR("Failed to retrieve font id: " << p_id << "\n Returning fallback font");
    DEBUG_SHOW_WINDOWS_DIALOG_BOX(L"Failed to load font, please verify game files");
    return fallBackFont;
}

const sf::SoundBuffer& AssetManager::GetSound(const std::string& p_id) const
{
    if (m_soundBuffers.find(p_id) != m_soundBuffers.end())
    {
        return m_soundBuffers.find(p_id)->second;
    }
    DEBUG_LOG_ERROR("Failed to retrieve sound id: " << p_id);
    throw std::runtime_error("Sound not found");
}
