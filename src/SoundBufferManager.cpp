#include <aSFML/SoundBufferManager.hpp>

sf::SoundBufferManager& sf::SoundBufferManager::GetInstance()
{
    static SoundBufferManager instance;
    return instance;
}

sf::SoundBufferManager::~SoundBufferManager()
{
    Clear();
}

sf::SoundBuffer& sf::SoundBufferManager::GetSoundBuffer(const std::string& path)
{
    SoundBufferMap::iterator it = m_soundBuffers.find(path);
    if(it == m_soundBuffers.end())
    {
        sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
        soundBuffer->LoadFromFile(path);
        m_soundBuffers.insert(std::pair<std::string, sf::SoundBuffer*>(path, soundBuffer));
        return *soundBuffer;
    }
    else
        return *(it->second);
}

void sf::SoundBufferManager::DeleteSoundBuffer(const sf::SoundBuffer& soundBuffer)
{
    for(SoundBufferMap::iterator it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
    {
        if(it->second == &soundBuffer)
        {
            delete &soundBuffer;
            m_soundBuffers.erase(it);
        }
    }
}

void sf::SoundBufferManager::DeleteSoundBuffer(const std::string& path)
{
    SoundBufferMap::iterator it = m_soundBuffers.find(path);

    if(it != m_soundBuffers.end())
    {
        delete it->second;
        m_soundBuffers.erase(it);
    }
}

void sf::SoundBufferManager::Clear()
{
    for(SoundBufferMap::iterator it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it)
        delete it->second;
    m_soundBuffers.clear();
}

sf::SoundBufferManager::SoundBufferManager()
{
}
