#ifndef ASFML_FONTMANAGER_HPP
#define ASFML_FONTMANAGER_HPP

#include <map>
#include <SFML/Graphics.hpp>

namespace sf
{
    class FontManager
    {
    public :
        typedef std::map<std::string, sf::Font*> FontMap;

        static FontManager& GetInstance();

        ~FontManager();

        sf::Font& GetFont(const std::string& path);

        void DeleteFont(const sf::Font& font);

        void DeleteFont(const std::string& path);

        void Clear();

    private :
        FontManager();

        std::map<std::string, sf::Font*> m_fonts;
    };
}

#endif // ASFML_FONTMANAGER_HPP
