#ifndef ASFML_SOUNDBUFFERMANAGER_HPP
#define ASFML_SOUNDBUFFERMANAGER_HPP

#include <map>
#include <SFML/Audio.hpp>

namespace sf
{
    class SoundBufferManager
    {
    public :
        typedef std::map<std::string, sf::SoundBuffer*> SoundBufferMap;

        static SoundBufferManager& GetInstance();

        ~SoundBufferManager();

        sf::SoundBuffer& GetSoundBuffer(const std::string& path);

        void DeleteSoundBuffer(const sf::SoundBuffer& soundBuffer);

        void DeleteSoundBuffer(const std::string& path);

        void Clear();

    private :
        SoundBufferManager();

        std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
    };
}

#endif // ASFML_SOUNDBUFFERMANAGER_HPP
