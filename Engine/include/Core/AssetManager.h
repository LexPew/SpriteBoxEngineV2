#pragma once
#include <filesystem>
#include <unordered_map>
#include <string>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "SpriteData.h"
#include "Debug/DebugMacros.h"

// Class: AssetManager
// Purpose: Manages assets such as sprites and fonts, also allows for saving and loading for scenes
//TODO: Add support for loading and saving so when a scene is loaded it can load all the assets it needs
//TODO: instead of loading them all at the start for every scene
class AssetManager
{
private:
    static AssetManager* instance;
    std::filesystem::path assetRoot; // Root directory for assets
    std::string assetRootString; //Workaround for cereal not being able to serialize std::filesystem::path

    //Sprites
    std::unordered_map<std::string, SpriteData> m_sprites; //Holds sprite data and via their ID
    std::unordered_map<std::string, std::string> m_spritePaths; //Holds the texture paths for sprites via their ID
    SpriteData nullSpriteData;

    //Textures
    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, std::string> m_texturePaths; //Holds the texture paths for textures via their ID

    //Fonts
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, std::string> m_fontPaths; //Holds the font paths for fonts via their ID
    sf::Font fallBackFont;

    //Audio
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, std::string> m_soundPaths; //Holds the sound paths for audio via their ID

    AssetManager();
    ~AssetManager()
    {
        m_sprites.clear();
        instance = nullptr;
    }

    void CreateNullSpriteData();
    void LoadFallBackFont();
public:
    static AssetManager& GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new AssetManager();
        }
        return *instance;
    }

    static void Cleanup()
    {
        delete instance;
    }

    void SetAssetRoot(const std::string& p_rootPath)
    {
        assetRootString = p_rootPath;
        assetRoot = p_rootPath;
    }

    std::string ResolvePath(const std::string& p_relativePath) const;

    //--SPRITE MANAGEMENT--

    /**
     * Loads a sprite using a json asset file
     * @param p_path File path of the json sprite asset
     */
    bool LoadSprite(const std::string& p_path);

    /**
     * Loads a font from a file
     * @param p_id
     * @param p_path File path of the font
     */
    bool LoadFont(const std::string& p_id, const std::string& p_path);

    /**
     * Loads a texture from a file
     * @param p_id
     * @param p_path File path of the texture
     */
    bool LoadTexture(const std::string& p_id, const std::string& p_path);

    /**
     * Loads a sound from a file
     * @param p_id
     * @param p_path File path of the sound
     */
    bool LoadSound(const std::string& p_id, const std::string& p_path);

    /**
     * Returns texture of texture(ID) if found and loaded
     * @param p_id Texture Id
     */
    const sf::Texture& GetTexture(const std::string& p_id) const;

    /**
     * Returns spriteData of sprite(ID) if found and loaded
     * @param p_id Sprite Id
     */
    const SpriteData& GetSprite(const std::string& p_id) const;

    /**
    * Returns font of font(ID) if found and loaded
    * @param p_id Font Id
    */
    const sf::Font& GetFont(const std::string& p_id) const;

    /**
    * Returns sound buffer of sound(ID) if found and loaded
    * @param p_id Sound Id
    */
    const sf::SoundBuffer& GetSound(const std::string& p_id) const;

    template <class Archive>
    void save(Archive& archive) const
    {

        DEBUG_LOG("Saving asset manager");
        archive(assetRootString, m_spritePaths, m_fontPaths, m_texturePaths, m_soundPaths);
    }

    template <class Archive>
    void load(Archive& archive)
    {

        DEBUG_LOG("Loading asset manager");
        archive(assetRootString, m_spritePaths, m_fontPaths, m_texturePaths, m_soundPaths);
        SetAssetRoot(assetRootString);
        DEBUG_LOG("Sprite path size " << m_spritePaths.size());
        for (auto& pair : m_spritePaths)
        {
            DEBUG_LOG("Sprite path " << pair.second);
            LoadSprite(pair.second);
        }
        for (auto& pair : m_fontPaths)
        {
            DEBUG_LOG("Font path " << pair.second);
            LoadFont(pair.first, pair.second);
        }
        for (auto& pair : m_texturePaths)
        {
            DEBUG_LOG("Texture path " << pair.second);
            LoadTexture(pair.first, pair.second);
        }
        for (auto& pair : m_soundPaths)
        {
            DEBUG_LOG("Sound path " << pair.second);
            LoadSound(pair.first, pair.second);
        }
    }
};