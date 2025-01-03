#include "Core/SoundPlayer.h"
#include "Core/AssetManager.h"
#include <SFML/Audio.hpp>

SoundPlayer* SoundPlayer::instance = nullptr;

SoundPlayer::SoundPlayer()
    : m_music(new sf::Music())
{
}

SoundPlayer::~SoundPlayer()
{
    delete m_music;
}

SoundPlayer& SoundPlayer::GetInstance()
{
    if (!instance)
    {
        instance = new SoundPlayer();
    }
    return *instance;
}

void SoundPlayer::Cleanup()
{
    delete instance;
    instance = nullptr;
}

void SoundPlayer::PlaySoundClip(const std::string& p_id)
{
    const sf::SoundBuffer& buffer = AssetManager::GetInstance().GetSound(p_id);
    if (m_sounds.find(p_id) == m_sounds.end())
    {
        m_sounds[p_id].setBuffer(buffer);
    }
    m_sounds[p_id].play();
}

void SoundPlayer::StopSoundClip(const std::string& p_id)
{
    if (m_sounds.find(p_id) != m_sounds.end())
    {
        m_sounds[p_id].stop();
    }
}

void SoundPlayer::PauseSound(const std::string& p_id)
{
    if (m_sounds.find(p_id) != m_sounds.end())
    {
        m_sounds[p_id].pause();
    }
}

void SoundPlayer::SetSoundVolume(const std::string& p_id, float volume)
{
    if (m_sounds.find(p_id) != m_sounds.end())
    {
        m_sounds[p_id].setVolume(volume);
    }
}

void SoundPlayer::PlayMusic(const std::string& p_path)
{
    if (!m_music->openFromFile(p_path))
    {
        throw std::runtime_error("Failed to load music: " + p_path);
    }
    m_music->play();
}

void SoundPlayer::StopMusic()
{
    m_music->stop();
}

void SoundPlayer::PauseMusic()
{
    m_music->pause();
}

void SoundPlayer::SetMusicVolume(float volume)
{
    m_music->setVolume(volume);
}
