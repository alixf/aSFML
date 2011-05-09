#ifndef ASFML_IMAGEMANAGER_HPP
#define ASFML_IMAGEMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace sf
{
    class ImageManager
    {
    public :
        typedef std::map<std::string, sf::Image*> ImageMap;

        static ImageManager& GetInstance();

        ~ImageManager();

        sf::Image& GetImage(const std::string& path);

        void DeleteImage(const sf::Image& image);

        void DeleteImage(const std::string& path);

        void Clear();

    private :
        ImageManager();

        std::map<std::string, sf::Image*> m_images;
    };
}

#endif // ASFML_IMAGEMANAGER_HPP
