#pragma once

#include <unordered_map>
#include <string>

namespace sf {
    class Sound;
    class SoundBuffer;
    class Music;
}

// Class: SoundPlayer
// Purpose: Handles the playing of sound effects and music, loading is done in AssetManager
class SoundPlayer
{
private:
    static SoundPlayer* instance;

    std::unordered_map<std::string, sf::Sound> m_sounds; // Holds sound instances
    sf::Music* m_music; // For background music

    SoundPlayer();
    ~SoundPlayer();

public:
    static SoundPlayer& GetInstance();

    static void Cleanup();

    void PlaySoundClip(const std::string& p_id);


    void StopSoundClip(const std::string& p_id);

    void PauseSound(const std::string& p_id);

    void SetSoundVolume(const std::string& p_id, float volume);

    void PlayMusic(const std::string& p_path);

    void StopMusic();

    void PauseMusic();

    void SetMusicVolume(float volume);
};
